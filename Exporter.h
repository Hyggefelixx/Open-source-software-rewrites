#ifndef EXPORTER_H
#define EXPORTER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Table.h"

class Exporter {
public:
    // 导出为 CSV 格式
    static void exportToCSV(const Table& table, const std::string& fileName) {
        std::ofstream outFile(fileName);
        if (!outFile.is_open()) {
            throw std::runtime_error("无法打开文件进行写入");
        }
        
        auto columnNames = table.getColumnNames();
        for (size_t i = 0; i < columnNames.size(); ++i) {
            outFile << columnNames[i];
            if (i < columnNames.size() - 1) outFile << ",";
        }
        outFile << "\n";
        
        auto rows = table.getData();
        for (const auto& row : rows) {
            for (size_t i = 0; i < row.size(); ++i) {
                outFile << row[i];
                if (i < row.size() - 1) outFile << ",";
            }
            outFile << "\n";
        }
        
        outFile.close();
    }
    
    // 导出为 JSON 格式
    static void exportToJSON(const Table& table, const std::string& fileName) {
        std::ofstream outFile(fileName);
        if (!outFile.is_open()) {
            throw std::runtime_error("无法打开文件进行写入");
        }
        
        outFile << "[\n";
        
        auto columnNames = table.getColumnNames();
        auto rows = table.getData();
        
        for (size_t i = 0; i < rows.size(); ++i) {
            outFile << "  {\n";
            for (size_t j = 0; j < columnNames.size(); ++j) {
                outFile << "    \"" << columnNames[j] << "\": \"" << rows[i][j] << "\"";
                if (j < columnNames.size() - 1) outFile << ",";
                outFile << "\n";
            }
            outFile << "  }";
            if (i < rows.size() - 1) outFile << ",";
            outFile << "\n";
        }
        
        outFile << "]\n";
        outFile.close();
    }
};

#endif
