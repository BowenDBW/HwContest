//
// Created by chenhong on 2023/3/15.
//

#ifndef HUAWEICONTEST_ROBOT_BEHAVIOR_H
#define HUAWEICONTEST_ROBOT_BEHAVIOR_H

#include <string>
#include <vector>
#include <iostream>



// 行为结点类，是所有行为结点的基类，提供执行接口和添加子结点接口
class BehaviorNode {
public:
    // 枚举类型，表示执行结果
    enum class Result {
        Success,
        Failure,
        Running
    };

    // 构造函数
    BehaviorNode(const std::string& name) : name_(name) {}

    // 虚析构函数
    virtual ~BehaviorNode() {}

    // 纯虚函数，执行行为，并返回结果
    virtual Result execute() = 0;

    // 添加子结点函数，将一个子结点添加到当前结点的末尾
    void addChild(BehaviorNode* child) {
        children_.push_back(child);
    }

protected:
    std::string name_; // 结点名称
    std::vector<BehaviorNode*> children_; // 子结点列表

};

// 行为树类，包含一个根结点，并提供执行接口
class BehaviorTree {
public:
    // 构造函数
    BehaviorTree(BehaviorNode* root) : root_(root) {}

    // 执行函数，返回结果
    BehaviorNode::Result execute() {
        return root_->execute();
    }

    // 添加子结点函数，将一个子结点添加到指定的父结点的末尾
    void addChild(BehaviorNode* parent, BehaviorNode* child) {
        parent->addChild(child);
    }

    // 获取根结点函数，返回根结点指针
    BehaviorNode* getRoot() {
        return root_;
    }

private:
    BehaviorNode* root_; // 根结点

};

// 复合结点的基类，有多个子结点
class CompositeNode : public BehaviorNode {
public:
    // 构造函数
    CompositeNode(const std::string& name) : BehaviorNode(name) {}

    // 添加子结点
    void addChild(BehaviorNode* child) {
        children_.push_back(child);
    }

protected:
    std::vector<BehaviorNode*> children_; // 子结点列表
};

// 序列结点，按顺序执行所有子结点，直到遇到失败或运行中的子结点，或者全部成功
class SequenceNode : public CompositeNode {
public:
    // 构造函数
    SequenceNode(const std::string& name) : CompositeNode(name), current_(0) {}

    // 执行函数，返回结果
    Result execute() override {
        while (current_ < children_.size()) {
            auto result = children_[current_]->execute();
            if (result == Result::Failure || result == Result::Running) {
                return result;
            }
            current_++;
        }
        current_ = 0;
        return Result::Success;
    }

private:
    size_t current_; // 当前执行的子结点索引
};

// 并行结点，同时执行所有子结点，直到遇到失败或全部成功或运行中（取决于策略）
class ParallelNode : public CompositeNode {
public:
    enum class Policy {
        RequireOne, // 只要有一个成功就算成功
        RequireAll, // 必须全部成功才算成功
    };

    ParallelNode(const std::string& name, Policy successPolicy, Policy failurePolicy)
            : CompositeNode(name), successPolicy_(successPolicy), failurePolicy_(failurePolicy) {}

    Result execute() override {
        size_t successCount = 0;
        size_t failureCount = 0;

        for (auto child : children_) {
            auto result = child->execute();
            if (result == Result::Success) {
                successCount++;
                if (successPolicy_ == Policy::RequireOne) {
                    return Result::Success;
                }
            } else if (result == Result::Failure) {
                failureCount++;
                if (failurePolicy_ == Policy::RequireOne) {
                    return Result::Failure;
                }
            } else {
                return Result::Running;
            }
        }

        if (failurePolicy_ == Policy::RequireAll && failureCount == children_.size()) {
            return Result::Failure;
        }

        if (successPolicy_ == Policy::RequireAll && successCount == children_.size()) {
            return Result::Success;
        }

        return Result::Running;
    }

private:
    Policy successPolicy_; // 成功策略
    Policy failurePolicy_; // 失败策略

};

// 装饰器结点的基类，有一个子结点，并对其执行结果进行修改或其他操作
class DecoratorNode : public BehaviorNode {
public:
    DecoratorNode(const std::string& name, BehaviorNode* child)
            : BehaviorNode(name), child_(child){}

protected:
    //子节点
    BehaviorNode* child_;

};

// 反转装饰器结点，把子结点的成功和失败结果反转过来
class InverterNode : public DecoratorNode {
public:
    // 构造函数
    InverterNode(const std::string& name, BehaviorNode* child)
            : DecoratorNode(name, child) {}

    // 执行函数，返回结果
    Result execute() override {
        auto result = child_->execute();
        if (result == Result::Success) {
            return Result::Failure;
        } else if (result == Result::Failure) {
            return Result::Success;
        } else {
            return Result::Running;
        }
    }
};

// 重复装饰器结点，重复执行子结点，直到遇到失败或运行中的结果，或者达到最大次数
class RepeaterNode : public DecoratorNode {
public:
    // 构造函数
    RepeaterNode(const std::string& name, BehaviorNode* child, int maxRepeat = -1)
            : DecoratorNode(name, child), maxRepeat_(maxRepeat), count_(0) {}

    // 执行函数，返回结果
    Result execute() override {
        while (true) {
            auto result = child_->execute();
            if (result == Result::Success) {
                count_++;
                if (maxRepeat_ > 0 && count_ >= maxRepeat_) {
                    count_ = 0;
                    return Result::Success;
                }
            } else {
                count_ = 0;
                return result;
            }
        }
    }

private:
    int maxRepeat_; // 最大重复次数，-1表示无限制
    int count_; // 当前重复次数

};



class PrintNode : public BehaviorNode {
public:
    // 构造函数
    PrintNode(const std::string& name, const std::string& message) : BehaviorNode(name), message_(message) {}

    // 执行函数，返回结果
    Result execute() override {
        std::cout << message_ << std::endl;
        return Result::Success;
    }

private:
    std::string message_; // 要打印的信息
};

// 选择结点类，继承自行为结点类，按顺序执行子结点，直到遇到一个返回成功或者正在运行的子结点，然后返回相同的结果。如果所有的子结点都返回失败，那么选择结点也返回失败。
class SelectorNode : public BehaviorNode {
public:
    // 构造函数
    SelectorNode(const std::string& name) : BehaviorNode(name) {}

    // 执行函数，重写父类的虚函数
    Result execute() override {
        // 遍历所有的子结点
        for (auto child : children_) {
            // 执行当前子结点，并获取结果
            Result result = child->execute();
            // 如果结果是成功或者正在运行，那么直接返回相同的结果
            if (result == Result::Success || result == Result::Running) {
                return result;
            }
        }
        // 如果所有的子结点都返回失败，那么选择结点也返回失败
        return Result::Failure;
    }

};

#endif //HUAWEICONTEST_ROBOT_BEHAVIOR_H

