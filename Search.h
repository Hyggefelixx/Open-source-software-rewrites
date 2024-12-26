#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Table.h"

class Search {
public:
    // 基于列名和查询内容的模糊查询
    static std::vector<std::vector<std::string>> search(const Table& table, const std::string& columnName, const std::string& query) {
        std::vector<std::vector<std::string>> result;
        
        auto columnNames = table.getColumnNames();
        auto it = std::find(columnNames.begin(), columnNames.end(), columnName);
        if (it == columnNames.end()) {
            throw std::runtime_error("未找到列名");
        }

        size_t columnIndex = std::distance(columnNames.begin(), it);
        auto rows = table.getData();

        for (const auto& row : rows) {
            if (row[columnIndex].find(query) != std::string::npos) {
                result.push_back(row);
            }
        }

        return result;
    }
};

#endif
