#ifndef UNDREDO_H
#define UNDREDO_H

#include <iostream>
#include <stack>
#include <vector>
#include "Table.h"

class UndoRedo {
public:
    // 撤销
    static void undo(Table& table) {
        if (!undoStack.empty()) {
            table = undoStack.top();  // 恢复到上一个状态
            undoStack.pop();
        } else {
            std::cout << "没有更多的撤销操作\n";
        }
    }

    // 重做
    static void redo(Table& table) {
        if (!redoStack.empty()) {
            table = redoStack.top();  // 恢复到重做的状态
            redoStack.pop();
        } else {
            std::cout << "没有更多的重做操作\n";
        }
    }

    // 保存当前状态
    static void saveState(const Table& table) {
        undoStack.push(table);
        // 清空重做栈
        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }

private:
    static std::stack<Table> undoStack;
    static std::stack<Table> redoStack;
};

// 初始化栈
std::stack<Table> UndoRedo::undoStack;
std::stack<Table> UndoRedo::redoStack;

#endif
