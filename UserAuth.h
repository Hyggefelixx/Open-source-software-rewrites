#ifndef USERAUTH_H
#define USERAUTH_H

#include <iostream>
#include <unordered_map>
#include <string>

class UserAuth {
public:
    // 添加用户
    static void addUser(const std::string& username, const std::string& password) {
        users[username] = password;
    }

    // 验证用户
    static bool authenticate(const std::string& username, const std::string& password) {
        auto it = users.find(username);
        if (it != users.end() && it->second == password) {
            return true;
        }
        return false;
    }

private:
    static std::unordered_map<std::string, std::string> users;
};

// 初始化用户数据
std::unordered_map<std::string, std::string> UserAuth::users;

#endif
