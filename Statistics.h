#ifndef STATISTICS_H
#define STATISTICS_H

#include <iostream>
#include <vector>
#include <cmath>
#include "Table.h"

class Statistics {
public:
    // 计算某列的均值
    static double mean(const Table& table, const std::string& columnName) {
        auto columnData = getColumnData(table, columnName);
        double sum = 0;
        for (const auto& value : columnData) {
            sum += std::stod(value);
        }
        return sum / columnData.size();
    }

    // 计算某列的方差
    static double variance(const Table& table, const std::string& columnName) {
        auto columnData = getColumnData(table, columnName);
        double avg = mean(table, columnName);
        double sumSquaredDiff = 0;
        for (const auto& value : columnData) {
            double diff = std::stod(value) - avg;
            sumSquaredDiff += diff * diff;
        }
        return sumSquaredDiff / columnData.size();
    }

    // 计算某列的标准差
    static double standardDeviation(const Table& table, const std::string& columnName) {
        return std::sqrt(variance(table, columnName));
    }

private:
    // 获取某列的数据
    static std::vector<std::string> getColumnData(const Table& table, const std::string& columnName) {
        auto columnNames = table.getColumnNames();
        auto it = std::find(columnNames.begin(), columnNames.end(), columnName);
        if (it == columnNames.end()) {
            throw std::runtime_error("未找到列名");
        }

        size_t columnIndex = std::distance(columnNames.begin(), it);
        auto rows = table.getData();
        std::vector<std::string> columnData;

        for (const auto& row : rows) {
            columnData.push_back(row[columnIndex]);
        }

        return columnData;
    }
};

#endif
