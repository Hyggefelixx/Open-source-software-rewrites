#include "Formatter.h"
#include <string>
#include <vector>
#include <map>

class MyJSON {
public:
    static std::string toJSON(const std::map<std::string, std::string>& data);
    static std::map<std::string, std::string> fromJSON(const std::string& jsonString);
};

class MyStringStream {
public:
    static std::string toString(int value);
    static std::string toString(double value);
    static std::vector<std::string> split(const std::string& str, char delimiter);
};

std::string MyJSON::toJSON(const std::map<std::string, std::string>& data) {
    std::ostringstream oss;
    oss << "{";
    for (auto it = data.begin(); it != data.end(); ++it) {
        oss << "\"" << it->first << "\": \"" << it->second << "\"";
        if (std::next(it) != data.end()) {
            oss << ", ";
        }
    }
    oss << "}";
    return oss.str();
}

std::map<std::string, std::string> MyJSON::fromJSON(const std::string& jsonString) {
    std::map<std::string, std::string> data;
    std::string key, value;
    size_t start_pos = 0, end_pos = 0;
    while ((start_pos = jsonString.find("\"", end_pos)) != std::string::npos) {
        end_pos = jsonString.find("\"", start_pos + 1);
        key = jsonString.substr(start_pos + 1, end_pos - start_pos - 1);

        start_pos = jsonString.find("\"", end_pos + 1);
        end_pos = jsonString.find("\"", start_pos + 1);
        value = jsonString.substr(start_pos + 1, end_pos - start_pos - 1);

        data[key] = value;
        end_pos = end_pos + 1;
    }
    return data;
}

std::string MyStringStream::toString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

std::string MyStringStream::toString(double value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

std::vector<std::string> MyStringStream::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void Formatter::toCSV(const std::vector<std::string>& column_names, const std::vector<std::vector<std::string>>& data, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file to write CSV");
    }
    
    // Write column names
    for (size_t i = 0; i < column_names.size(); ++i) {
        file << column_names[i];
        if (i < column_names.size() - 1) {
            file << ",";
        }
    }
    file << "\n";
    
    // Write data rows
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }

    file.close();
}

void Formatter::toJSON(const std::vector<std::string>& column_names, const std::vector<std::vector<std::string>>& data, const std::string& filename) {
    Json::Value root;
    Json::StreamWriterBuilder writer;
    
    for (const auto& row : data) {
        Json::Value json_row;
        for (size_t i = 0; i < column_names.size(); ++i) {
            json_row[column_names[i]] = row[i];
        }
        root.append(json_row);
    }
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file to write JSON");
    }

    file << Json::writeString(writer, root);
    file.close();
}
