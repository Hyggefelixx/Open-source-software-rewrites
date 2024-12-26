#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <vector>

class Validator {
public:
    static bool validateInteger(const std::string& str);
    static bool validateFloat(const std::string& str);
    static bool validateEmail(const std::string& str);
    static bool validateDate(const std::string& str);
    static bool validateRowData(const std::vector<std::string>& row, const std::vector<std::string>& column_types);
};

#endif
