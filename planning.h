//
// Created by bowen on 23-3-14.
//

#ifndef HUAWEICONTEST_PLANNING_H
#define HUAWEICONTEST_PLANNING_H

/**
 * <p>
 * 这个类是所有决策模型的基类，之后几天的主要任务都是围绕如何写决策树展开所有
 * 决策树都需要实现 planningLoop() 方法，该方法会在 main 函数中作为一个单
 * 独的线程启动，大致逻辑是：循环开始去 Router::std::vector<RobotState>
 * 中询问这 4 个 RobotState 的 isRunning() 是否为 false, 如果为 false，
 * 启动决策树并给该机器人规划一个新的任务并通过该类中 setNewTask() 方法将该任
 * 务放入 RobotState 里执行。
 * </p>
 * <br/>
 * <p>
 * 所有任务完成后 Navigation 会将 isRunning 再次设置为 false，决策树模型便
 * 会再一次调用。
 * </p>
 */
class Planning {
public:
    // 纯虚函数，必须在子类中实现
    [[noreturn]]virtual void planningLoop() = 0;

};


#endif //HUAWEICONTEST_PLANNING_H
