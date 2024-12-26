#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Logger {
public:
    static void log(const std::string& message) {
        std::ofstream logFile("log.txt", std::ios_base::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("无法打开日志文件");
        }

        // 获取当前时间
        std::time_t currentTime = std::time(nullptr);
        std::tm* timeInfo = std::localtime(&currentTime);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);

        logFile << "[" << buffer << "] " << message << "\n";
        logFile.close();
    }
};

#endif
