//
// Created by chenhong on 2023/3/15.
//

#ifndef HUAWEICONTEST_ROBOT_BEHAVIOR_H
#define HUAWEICONTEST_ROBOT_BEHAVIOR_H

#include <vector>
#include <string>

// 行为树的基类，定义了公共的接口和属性
class BehaviorTree {
protected:
    std::string name; // 节点的名称
    std::vector<BehaviorTree*> children; // 节点的子节点列表

public:
    // 枚举类型，表示节点的状态
    enum class Status {
        Success,
        Failure,
        Running
    };

    // 构造函数，初始化名称和子节点列表
    BehaviorTree(const std::string& name);

    // 虚析构函数，释放子节点的内存
    virtual ~BehaviorTree() {
        for (auto child : children) {
            delete child;
        }
    }

    // 纯虚函数，执行节点的逻辑，并返回状态信息
    virtual Status tick() = 0;
};

// 行为树的组合节点类，继承自基类，并添加了添加子节点和获取子节点数量的方法
class CompositeNode : public BehaviorTree {
public:
    // 构造函数，调用基类构造函数并传入名称参数
    CompositeNode(const std::string& name);

    // 添加一个子节点到列表中
    void addChild(BehaviorTree* child);

    // 获取子节点列表的大小（即数量）
    int getChildCount() const;
};

// 行为树的选择器节点类，继承自组合节点类，并实现了选择器逻辑：依次执行每个子节点，直到有一个返回成功或运行中，则返回该状态；如果所有子节点都返回失败，则返回失败。
class SelectorNode : public CompositeNode {
private:
    int current; // 记录当前执行到哪个子节点的索引

public:
    // 构造函数，调用基类构造函数并传入名称参数，默认设置当前索引为 0
    SelectorNode(const std::string& name);

    // 执行选择器逻辑，并返回状态信息
    Status tick() override {
        while (true) {
            if (current >= getChildCount()) {
                return Status::Failure;
            }
            auto status = children[current]->tick();
            if (status != Status::Failure) {
                return status;
            }
            current++;
        }
    }

};

// 行为树的序列器节点类，继承自组合节点类，并实现了序列器逻辑：依次执行每个子节点，直到有一个返回失败或运行中，则返回该状态；如果所有子节点都返回成功，则返回成功。
class SequenceNode : public CompositeNode {
private:
    int current; // 记录当前执行到哪个子节点的索引

public:
    // 构造函数，调用基类构造函数并传入名称参数，默认设置当前索引为 0
    SequenceNode(const std::string& name);

    // 执行序列器逻辑，并返回状态信息
    Status tick() override {
        while (true) {
            if (current >= getChildCount()) {
                return Status::Success;
            }

            auto status = children[current]->tick();
            //如果不成功
            if (status != Status::Success) {
                return status;
            }
            current++;
        }
    }
};

// 行为树的动作节点类，继承自基类，并实现了一个简单的打印动作
class ActionNode : public BehaviorTree {
public:
    // 构造函数，调用基类构造函数并传入名称参数
    ActionNode(const std::string& name);

    // 执行打印动作，并返回成功状态
    Status tick() override {
        std::cout << name << " is running." << std::endl;
        return Status::Success;
    }
};

// 行为树的条件节点类，继承自基类，并实现了一个简单的判断条件
class ConditionNode : public BehaviorTree {
private:
    bool condition; // 判断条件的值

public:
    // 构造函数，调用基类构造函数并传入名称参数和判断条件参数
    ConditionNode(const std::string& name, bool condition);

    // 根据判断条件返回成功或失败状态
    Status tick() override {
        if (condition) {
            return Status::Success;
        } else {
            return Status::Failure;
        }
    }
};

#endif //HUAWEICONTEST_ROBOT_BEHAVIOR_H

