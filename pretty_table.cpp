#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "Exporter.h"
#include "Merger.h"
#include "Sorter.h"
#include "TableEditor.h"
#include "Importer.h"

using namespace std;

// Alignment Enum
enum Alignment {
    LEFT,
    RIGHT,
    CENTER
};

// Style Class
class Style {
public:
    char vertical_border;
    char horizontal_border;
    char corner;
    Alignment alignment;

    Style(char vertical = '|', char horizontal = '-', char corner = '+', Alignment align = LEFT)
        : vertical_border(vertical), horizontal_border(horizontal), corner(corner), alignment(align) {}
};

// Custom implementation of map (simple key-value pair)
struct KeyValuePair {
    string key;
    size_t value;
};

class CustomMap {
private:
    vector<KeyValuePair> entries;

public:
    void insert(const string& key, size_t value) {
        for (auto& entry : entries) {
            if (entry.key == key) {
                entry.value = value;
                return;
            }
        }
        entries.push_back({key, value});
    }

    size_t at(const string& key) const {
        for (const auto& entry : entries) {
            if (entry.key == key) {
                return entry.value;
            }
        }
        throw runtime_error("Key not found");
    }

    bool contains(const string& key) const {
        for (const auto& entry : entries) {
            if (entry.key == key) {
                return true;
            }
        }
        return false;
    }

    void erase(const string& key) {
        for (auto it = entries.begin(); it != entries.end(); ++it) {
            if (it->key == key) {
                entries.erase(it);
                return;
            }
        }
    }

    vector<KeyValuePair>& getEntries() {
        return entries;
    }
};

// Custom exception handling
class InvalidArgumentException {
public:
    string message;
    InvalidArgumentException(const string& msg) : message(msg) {}
};

class OutOfRangeException {
public:
    string message;
    OutOfRangeException(const string& msg) : message(msg) {}
};

class RuntimeException {
public:
    string message;
    RuntimeException(const string& msg) : message(msg) {}
};

// Table Class
class Table {
private:
    vector<string> column_names;
    vector<vector<string>> data;
    Style style;
    size_t column_count;
    CustomMap column_indices;

    // Helper to compute column widths
    vector<size_t> computeColumnWidths() const {
        vector<size_t> widths(column_count, 0);
        for (size_t i = 0; i < column_count; ++i) {
            widths[i] = column_names[i].length();
            for (const auto& row : data) {
                if (i < row.size()) {
                    widths[i] = max(widths[i], row[i].length());
                }
            }
        }
        return widths;
    }

    // Helper to align text
    string alignText(const string& text, size_t width, Alignment align) const {
        if (align == LEFT) {
            return text + string(width - text.length(), ' ');
        } else if (align == RIGHT) {
            return string(width - text.length(), ' ') + text;
        } else {
            size_t pad_left = (width - text.length()) / 2;
            size_t pad_right = width - text.length() - pad_left;
            return string(pad_left, ' ') + text + string(pad_right, ' ');
        }
    }

    // Helper to print a row
    void printRow(const vector<string>& row, const vector<size_t>& widths) const {
        cout << style.vertical_border;
        for (size_t i = 0; i < column_count; ++i) {
            if (i < row.size()) {
                cout << " " << alignText(row[i], widths[i], style.alignment) << " ";
            } else {
                cout << " " << string(widths[i], ' ') << " ";
            }
            cout << style.vertical_border;
        }
        cout << endl;
    }

    // Helper to print a separator row
    void printSeparator(const vector<size_t>& widths) const {
        cout << style.corner;
        for (size_t i = 0; i < column_count; ++i) {
            cout << string(widths[i] + 2, style.horizontal_border) << style.corner;
        }
        cout << endl;
    }

public:
    // Constructor
    Table(const vector<string>& columns, const Style& style = Style())
        : column_names(columns), style(style), column_count(columns.size()) {
        for (size_t i = 0; i < columns.size(); ++i) {
            column_indices.insert(columns[i], i);
        }
    }

    // Add a row to the table
    void addRow(const vector<string>& row) {
        if (row.size() > column_count) {
            throw InvalidArgumentException("Row size exceeds column count");
        }
        data.push_back(row);
    }

    // Add a column to the table
    void addColumn(const string& column_name, const vector<string>& column_data) {
        column_names.push_back(column_name);
        column_indices.insert(column_name, column_count);
        ++column_count;
        for (size_t i = 0; i < max(data.size(), column_data.size()); ++i) {
            if (i >= data.size()) {
                data.emplace_back(vector<string>(column_count - 1, ""));
            }
            if (i < column_data.size()) {
                data[i].push_back(column_data[i]);
            } else {
                data[i].push_back("");
            }
        }
    }

    // Remove a column
    void removeColumn(const string& column_name) {
        if (!column_indices.contains(column_name)) {
            throw InvalidArgumentException("Column not found");
        }
        size_t index = column_indices.at(column_name);
        column_names.erase(column_names.begin() + index);
        column_indices.erase(column_name);
        for (auto& row : data) {
            if (index < row.size()) {
                row.erase(row.begin() + index);
            }
        }
        --column_count;
        for (auto& pair : column_indices.getEntries()) {
            if (pair.value > index) {
                --pair.value;
            }
        }
    }

    // Set table style
    void setStyle(const Style& new_style) {
        style = new_style;
    }

    // Print the table to the console
    void print() const {
        vector<size_t> widths = computeColumnWidths();
        printSeparator(widths);
        printRow(column_names, widths);
        printSeparator(widths);
        for (const auto& row : data) {
            printRow(row, widths);
        }
        printSeparator(widths);
    }

    // Save the table to a file
    void saveToFile(const string& file_name, bool append = false) const {
        FILE* file = fopen(file_name.c_str(), append ? "a" : "w");
        if (!file) {
            throw RuntimeException("Could not open file");
        }

        vector<size_t> widths = computeColumnWidths();
        auto writeSeparator = [&]() {
            fputc(style.corner, file);
            for (size_t i = 0; i < column_count; ++i) {
                for (size_t j = 0; j < widths[i] + 2; ++j) {
                    fputc(style.horizontal_border, file);
                }
                fputc(style.corner, file);
            }
            fputc('\n', file);
        };

        auto writeRow = [&](const vector<string>& row) {
            fputc(style.vertical_border, file);
            for (size_t i = 0; i < column_count; ++i) {
                string text = (i < row.size()) ? alignText(row[i], widths[i], style.alignment) : string(widths[i], ' ');
                fprintf(file, " %s %c", text.c_str(), style.vertical_border);
            }
            fputc('\n', file);
        };

        writeSeparator();
        writeRow(column_names);
        writeSeparator();
        for (const auto& row : data) {
            writeRow(row);
        }
        writeSeparator();
        fclose(file);
    }

    // Get column names
    vector<string> getColumnNames() const {
        return column_names;
    }

    // Get a specific row by index
    vector<string> getRow(size_t index) const {
        if (index >= data.size()) {
            throw OutOfRangeException("Row index out of range");
        }
        return data[index];
    }

    // Sort table by a specific column
    void sortByColumn(const string& column_name, bool ascending = true) {
        if (!column_indices.contains(column_name)) {
            throw InvalidArgumentException("Column not found");
        }
        size_t index = column_indices.at(column_name);
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = i + 1; j < data.size(); ++j) {
                bool condition = ascending ? (data[i][index] > data[j][index]) : (data[i][index] < data[j][index]);
                if (condition) {
                    swap(data[i], data[j]);
                }
            }
        }
    }

    // Search table by a specific column
    vector<vector<string>> searchByColumn(const string& column_name, const string& value) const {
        if (!column_indices.contains(column_name)) {
            throw InvalidArgumentException("Column not found");
        }
        size_t index = column_indices.at(column_name);
        vector<vector<string>> results;
        for (const auto& row : data) {
            if (index < row.size() && row[index] == value) {
                results.push_back(row);
            }
        }
        return results;
    }
};

int main() {
    Table table({"Name", "Age", "City"});
    table.addRow({"Alice", "30", "New York"});
    table.addRow({"Bob", "25", "Los Angeles"});
    table.addRow({"Charlie", "35", "Chicago"});
    
    bool running = true;
    while (running) {
        std::cout << "选择操作：\n";
        std::cout << "1. 导出为CSV\n";
        std::cout << "2. 合并表格\n";
        std::cout << "3. 排序\n";
        std::cout << "4. 编辑表格\n";
        std::cout << "5. 退出\n";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                Exporter::exportToCSV(table, "output.csv");
                std::cout << "表格已导出为 CSV 文件。\n";
                break;
            case 2: {
                Table table2({"Name", "Age", "City"});
                table2.addRow({"David", "40", "Houston"});
                Table mergedTable = Merger::merge(table, table2);
                std::cout << "表格已合并。\n";
                break;
            }
            case 3:
                Sorter::sortByColumn(table, "Age", true);
                std::cout << "表格已按年龄升序排序。\n";
                break;
            case 4:
                TableEditor::editCell(table, 1, 1, "26");
                std::cout << "表格已编辑。\n";
                break;
            case 5:
                running = false;
                break;
            default:
                std::cout << "无效的选择。\n";
                break;
        }
    }
    return 0;
}
