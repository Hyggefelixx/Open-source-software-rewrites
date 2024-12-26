#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <map>

using namespace std;

enum Alignment {
    LEFT,
    RIGHT,
    CENTER
};

class Style {
public:
    char vertical_border;
    char horizontal_border;
    char corner;
    Alignment alignment;

    Style(char vertical = '|', char horizontal = '-', char corner = '+', Alignment align = LEFT);
};

class Table {
private:
    vector<string> column_names;
    vector<vector<string>> data;
    Style style;
    size_t column_count;
    map<string, size_t> column_indices;

    vector<size_t> computeColumnWidths() const;
    string alignText(const string& text, size_t width, Alignment align) const;
    void printRow(const vector<string>& row, const vector<size_t>& widths) const;
    void printSeparator(const vector<size_t>& widths) const;

public:
    Table(const vector<string>& columns, const Style& style = Style());
    void addRow(const vector<string>& row);
    void addColumn(const string& column_name, const vector<string>& column_data);
    void removeColumn(const string& column_name);
    void setStyle(const Style& new_style);
    void print() const;
    void saveToFile(const string& file_name, bool append = false) const;
    vector<string> getColumnNames() const;
    vector<string> getRow(size_t index) const;
    void sortByColumn(const string& column_name, bool ascending = true);
    vector<vector<string>> searchByColumn(const string& column_name, const string& value) const;
    void importFromCSV(const string& filename);
    void modifyCell(size_t row_index, size_t column_index, const string& value);
    void bulkDeleteRows(const string& column_name, const string& value);
    map<string, pair<string, string>> getDataStatistics() const;
};

#endif
