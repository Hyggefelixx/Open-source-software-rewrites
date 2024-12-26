#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <string>

class Filter {
public:
    static std::vector<std::vector<std::string>> filterByColumn(const std::vector<std::vector<std::string>>& data, size_t column_index, const std::string& value);
    static std::vector<std::vector<std::string>> paginate(const std::vector<std::vector<std::string>>& data, size_t page, size_t page_size);
};

#endif
