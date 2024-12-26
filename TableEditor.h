#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <iostream>
#include <vector>
#include <string>
#include "Table.h"

class TableEditor {
public:
    // 编辑表格中的单元格
    static void editCell(Table& table, size_t rowIndex, size_t colIndex, const std::string& newValue) {
        auto rows = table.getData();
        
        if (rowIndex >= rows.size()) {
            throw std::out_of_range("行索引超出范围");
        }
        if (colIndex >= rows[rowIndex].size()) {
            throw std::out_of_range("列索引超出范围");
        }
        
        rows[rowIndex][colIndex] = newValue; // 修改单元格值
        table.setData(rows);
    }

    // 删除指定行
    static void deleteRow(Table& table, size_t rowIndex) {
        auto rows = table.getData();
        
        if (rowIndex >= rows.size()) {
            throw std::out_of_range("行索引超出范围");
        }
        
        rows.erase(rows.begin() + rowIndex); // 删除指定行
        table.setData(rows);
    }

    // 删除指定列
    static void deleteColumn(Table& table, size_t colIndex) {
        auto columnNames = table.getColumnNames();
        if (colIndex >= columnNames.size()) {
            throw std::out_of_range("列索引超出范围");
        }

        // 删除指定列
        for (auto& row : table.getData()) {
            row.erase(row.begin() + colIndex);
        }
        
        columnNames.erase(columnNames.begin() + colIndex);
        table.setColumnNames(columnNames); // 更新列名
    }
};

#endif
