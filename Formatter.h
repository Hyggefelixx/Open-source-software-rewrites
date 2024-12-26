#ifndef FORMATTER_H
#define FORMATTER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Formatter {
public:
    static void toCSV(const std::vector<std::string>& column_names, const std::vector<std::vector<std::string>>& data, const std::string& filename);
    static void toJSON(const std::vector<std::string>& column_names, const std::vector<std::vector<std::string>>& data, const std::string& filename);
};

#endif
