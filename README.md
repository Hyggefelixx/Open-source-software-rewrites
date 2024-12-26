# Open-source-software-rewrites
# PrettyTableCPP 项目介绍

## 一、项目背景
PrettyTable 原本是用于生成 ASCII 表格的轻量级库，在命令行或简单报告中格式化输出数据方面较为常用。通过使用 C++ 对其重写，能够显著提升性能，并赋予项目更高效且可定制化的表格格式化能力。

## 二、项目概览
- **目标**：打造一个高效、可扩展的 C++ 库，实现将数据格式化为表格样式，具备表格样式自定义、数据动态插入、列对齐以及宽度自动调整等特性。
- **名称**：PrettyTableCPP
- **语言**：C++
- **依赖**：仅依赖标准库，无外部依赖
- **目标用户**：主要面向开发者、研究人员以及系统管理员

## 三、核心模块设计

### （一）表格管理模块（Table Manager）
- 负责表格整体布局与样式的管理。
- 支持行、列的动态添加与删除操作。
- 提供接口，可用于自定义标题、边框、对齐方式以及单元格宽度等属性。

### （二）行列操作模块（Row & Column Operations）
- 对单行、单列的数据及其属性进行管理。
- 能够依据数据长度动态地调整列宽。
- 提供多种对齐选项，包括左对齐、右对齐和居中对齐。

### （三）样式控制模块（Style Controller）
- 提供可配置的边框、分隔符以及对齐方式。
- 支持多种预定义样式，如简约风格、加粗风格等。
- 允许用户自定义单元格的填充字符，例如 `|`、`-`、`=` 等。

### （四）输入输出模块（IO Module）
- 提供格式化表格的输出接口。
- 支持将表格打印到控制台，或者保存为文本文件。

## 四、核心功能描述

### （一）表格初始化
通过以下方式初始化一个空表格，并指定列数和列名：
```cpp
Table table({"Name", "Age", "City"});
```
### （二）数据动态插入
添加单行、单列数据，并自动调整列宽。  
```cpp 
table.addRow({"Alice", "30", "New York"});
```
### （三）样式设置
支持设置表格的边框字符、对齐方式、列宽限制。    
```cpp
table.setStyle(BoldStyle); // 设置加粗风格  
table.setAlignment(CENTER); // 设置列居中对齐
```
### （四）输出接口
将表格打印到控制台，并保存为 .txt 文件，支持追加模式。  
```cpp
table.print(); // 输出到控制台  
table.saveToFile("output.txt"); // 保存到文件  
```
### （五）多样式支持
支持预定义样式：简约风格、Markdown 风格、加粗边框等。  
自定义样式接口：允许用户指定分隔符、填充字符等。  

## 五、类与方法设计
**Table 类**
```cpp
属性：  
vector<string> column_names;  
vector<vector<string>> data;  
Style style;  

方法：  
Table(const vector<string>& column_names);  
void addRow(const vector<string>& row);  
void addColumn(const string& column_name, const vector<string>& column_data);  
void setStyle(const Style& style);  
void print() const;  
void saveToFile(const string& file_name, bool append = false) const;
```

**Style 类**
```cpp
属性：  
char vertical_border;  
char horizontal_border;  
char corner;  
Alignment alignment; // 左、右、居中  
方法：  
Style(char vertical, char horizontal, char corner, Alignment align); 
Alignment 枚举值： LEFT, RIGHT, CENTER
```
## 六、项目扩展性
- **支持 CSV 文件输入输出：** 
  提供从 CSV 文件读取数据生成表格的功能。
  
- **支持国际化（Unicode 支持）：** 
  兼容非拉丁字符集（如中文、日文）。  

- **性能优化：**
  使用多线程优化大表格输出（行级别并行）。  

- **跨平台支持：** 
  确保在 Windows 和 Linux 下无差异运行。  

## 七、项目使用案例
```cpp
#include "PrettyTable.h"  
int main() {  
    Table table({"Name", "Age", "City"});  
    table.addRow({"Alice", "30", "New York"});  
    table.addRow({"Bob", "25", "Los Angeles"});  
    table.setStyle(Style('|', '-', '+', CENTER));  
    table.print();  
    table.saveToFile("output.txt");  
    return 0;  
}  
```
## 八、学习与应用价值   
- 学习 C++ 动态内存管理与数据结构的设计。  
- 掌握面向对象设计原则，尤其是模块化和类封装技术。  
- 优化 I/O 性能，提升对复杂系统的理解能力。  
- 为 C++ 项目开发者提供更灵活的表格工具，有助于生成更美观的输出。
