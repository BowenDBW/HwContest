//
// Created by chenhong on 2023/3/15.
//
#include <iostream>
#include "robot_behavior.h"


// 行为树的动作节点类，继承自基类，并实现了一个简单的打印动作
class ActionNode : public BehaviorTree {
public:
    // 构造函数，调用基类构造函数并传入名称参数
    ActionNode(const std::string& name) : BehaviorTree(name) {}

    // 执行打印动作，并返回成功状态
    Status tick() override {
        std::cout << name << " is running." << std::endl;
        return Status::Success;
    }
};

// 行为树的条件节点类，继承自基类，并实现了一个简单的判断条件
class ConditionNode : public BehaviorTree {
public:
    // 构造函数，调用基类构造函数并传入名称参数和判断条件参数
    ConditionNode(const std::string& name, bool condition) : BehaviorTree(name), condition(condition) {}

    // 根据判断条件返回成功或失败状态
    Status tick() override {
        if (condition) {
            return Status::Success;
        } else {
            return Status::Failure;
        }
    }

private:
    bool condition; // 判断条件的值
};

