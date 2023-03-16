//
// Created by chenhong on 2023/3/15.
//
#include <iostream>
#include "robot_behavior.h"

BehaviorTree::BehaviorTree(const std::string &name) : name(name), children()  {

}

/*
 * CompositeNode构造函数
 */
CompositeNode::CompositeNode(const std::string &name) : BehaviorTree(name) {

}

//添加子节点
void CompositeNode::addChild(BehaviorTree *child) {
    children.push_back(child);
}

// 获取子节点列表的大小（即数量）
int CompositeNode::getChildCount() const {
    return children.size();
}


// 构造函数，调用基类构造函数并传入名称参数，默认设置当前索引为 0
SelectorNode::SelectorNode(const std::string& name) : CompositeNode(name), current(0) {

}

// 构造函数，调用基类构造函数并传入名称参数，默认设置当前索引为 0
SequenceNode::SequenceNode(const std::string& name) : CompositeNode(name), current(0) {

}


// 构造函数，调用基类构造函数并传入名称参数
ActionNode::ActionNode(const std::string& name) : BehaviorTree(name) {

}

// 构造函数，调用基类构造函数并传入名称参数和判断条件参数
ConditionNode::ConditionNode(const std::string& name, bool condition) : BehaviorTree(name), condition(condition) {

}