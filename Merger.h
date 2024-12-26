#ifndef MERGER_H
#define MERGER_H

#include <iostream>
#include <vector>
#include <string>
#include "Table.h"

class Merger {
public:
    // 合并两个表格，假设它们有相同的列结构
    static Table merge(const Table& table1, const Table& table2) {
        if (table1.getColumnNames() != table2.getColumnNames()) {
            throw std::runtime_error("表格列名不一致，无法合并");
        }
        
        Table mergedTable(table1.getColumnNames()); // 创建一个新的表格
        
        // 合并两个表格的数据
        auto rows1 = table1.getData();
        auto rows2 = table2.getData();
        
        for (const auto& row : rows1) {
            mergedTable.addRow(row);
        }
        for (const auto& row : rows2) {
            mergedTable.addRow(row);
        }
        
        return mergedTable;
    }
};

#endif
