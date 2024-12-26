#ifndef IMPORTER_H
#define IMPORTER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Table.h"

class Importer {
public:
    // 从 CSV 文件导入数据
    static Table importFromCSV(const std::string& fileName) {
        std::ifstream inFile(fileName);
        if (!inFile.is_open()) {
            throw std::runtime_error("无法打开文件进行读取");
        }

        std::string line;
        std::getline(inFile, line); // 读取列名
        std::vector<std::string> columnNames;
        std::stringstream ss(line);
        std::string column;
        
        while (std::getline(ss, column, ',')) {
            columnNames.push_back(column);
        }
        
        Table table(columnNames);

        while (std::getline(inFile, line)) {
            std::vector<std::string> row;
            std::stringstream rowStream(line);
            std::string cell;
            
            while (std::getline(rowStream, cell, ',')) {
                row.push_back(cell);
            }
            
            table.addRow(row);
        }

        inFile.close();
        return table;
    }

    // 从 JSON 文件导入数据
    static Table importFromJSON(const std::string& fileName) {
        // 这里简化了 JSON 解析过程，假设 JSON 格式简单，实际应用中需要使用 JSON 解析库
        std::ifstream inFile(fileName);
        if (!inFile.is_open()) {
            throw std::runtime_error("无法打开文件进行读取");
        }

        Table table;
        // 解析过程省略...
        
        inFile.close();
        return table;
    }
};

#endif
