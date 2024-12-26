#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include <vector>
#include <string>

class Aggregator {
public:
    static double sumColumn(const std::vector<std::vector<std::string>>& data, size_t column_index);
    static double averageColumn(const std::vector<std::vector<std::string>>& data, size_t column_index);
};

#endif
