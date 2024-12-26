#include "Validator.h"
#include <string>
#include <vector>

class MyRegex {
public:
    static bool match(const std::string& pattern, const std::string& text);
    static bool matchInt(const std::string& text);
    static bool matchFloat(const std::string& text);
    static bool matchEmail(const std::string& text);
    static bool matchDate(const std::string& text);
};

class MyException {
public:
    MyException(const std::string& message) : message_(message) {}
    const std::string& what() const { return message_; }
    
private:
    std::string message_;
};

bool MyRegex::match(const std::string& pattern, const std::string& text) {

    return text.find(pattern) != std::string::npos;
}

bool MyRegex::matchInt(const std::string& text) {
    // 匹配简单的整数
    return !text.empty() && std::all_of(text.begin(), text.end(), ::isdigit);
}

bool MyRegex::matchFloat(const std::string& text) {
    // 简单匹配浮点数，支持负数
    size_t dot_count = std::count(text.begin(), text.end(), '.');
    return !text.empty() && dot_count <= 1 && std::all_of(text.begin(), text.end(), [](char c) {
        return ::isdigit(c) || c == '.' || c == '-';
    });
}

bool MyRegex::matchEmail(const std::string& text) {
    size_t at_pos = text.find('@');
    size_t dot_pos = text.find('.', at_pos);
    return at_pos != std::string::npos && dot_pos != std::string::npos && dot_pos > at_pos;
}

bool MyRegex::matchDate(const std::string& text) {
    // 简单匹配日期格式 YYYY-MM-DD
    if (text.size() != 10) return false;
    return text[4] == '-' && text[7] == '-';
}

bool Validator::validateInteger(const std::string& str) {
    std::regex pattern("^[+-]?[0-9]+$");
    return std::regex_match(str, pattern);
}

bool Validator::validateFloat(const std::string& str) {
    std::regex pattern("^[+-]?([0-9]*[.])?[0-9]+$");
    return std::regex_match(str, pattern);
}

bool Validator::validateEmail(const std::string& str) {
    std::regex pattern("[\\w-]+(\\.[\\w-]+)*@([\\w-]+\\.)+[a-zA-Z]{2,7}");
    return std::regex_match(str, pattern);
}

bool Validator::validateDate(const std::string& str) {
    std::regex pattern("\\d{4}-\\d{2}-\\d{2}");
    return std::regex_match(str, pattern);
}

bool Validator::validateRowData(const std::vector<std::string>& row, const std::vector<std::string>& column_types) {
    for (size_t i = 0; i < row.size(); ++i) {
        if (column_types[i] == "int" && !validateInteger(row[i])) {
            throw std::invalid_argument("Invalid integer value at row " + std::to_string(i));
        } else if (column_types[i] == "float" && !validateFloat(row[i])) {
            throw std::invalid_argument("Invalid float value at row " + std::to_string(i));
        } else if (column_types[i] == "email" && !validateEmail(row[i])) {
            throw std::invalid_argument("Invalid email value at row " + std::to_string(i));
        } else if (column_types[i] == "date" && !validateDate(row[i])) {
            throw std::invalid_argument("Invalid date value at row " + std::to_string(i));
        }
    }
    return true;
}
