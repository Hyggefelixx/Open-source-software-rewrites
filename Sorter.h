#ifndef SORTER_H
#define SORTER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Table.h"

class Sorter {
public:
    // 按列排序，支持升序和降序
    static void sortByColumn(Table& table, const std::string& columnName, bool ascending = true) {
        auto columnNames = table.getColumnNames();
        auto columnData = table.getData();
        
        // 查找该列索引
        auto it = std::find(columnNames.begin(), columnNames.end(), columnName);
        if (it == columnNames.end()) {
            throw std::runtime_error("未找到列名");
        }
        
        size_t columnIndex = std::distance(columnNames.begin(), it);
        
        // 排序
        std::sort(columnData.begin(), columnData.end(), [&](const std::vector<std::string>& row1, const std::vector<std::string>& row2) {
            if (ascending) {
                return row1[columnIndex] < row2[columnIndex];
            } else {
                return row1[columnIndex] > row2[columnIndex];
            }
        });
        
        table.setData(columnData); // 设置排序后的数据
    }
};

#endif
