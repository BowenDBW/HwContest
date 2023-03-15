//
// Created by bowen on 23-3-15.
//

#ifndef HUAWEICONTEST_ROUTER_H
#define HUAWEICONTEST_ROUTER_H

#include "game_map.h"

#include <vector>
#include <cmath>

#define UNLOCK (-1)
#define FREE_STATE 0

/**
 * 销售时刻表
 * 当有机器人决定去第 index 个工作台卖 material_type 这种物品时，就会显示
 * 其到达大约时刻 arrival_frame，没有机器人这么操作时 arrival_frame 就会
 * 为 UNLOCK 状态即 -1.
 */
struct SellTimeTable{
    int index;
    int material_type;
    int arrival_frame;
};

/**
 * 抽取工作台中不随帧而变的属性成为一个类，方便分析
 */
class WorkshopConstData {
private:
    Point2D *point{};
    int type;
public:
    WorkshopConstData(Point2D* point, int type);
    Point2D& getPosition();
    int getType() const;
};

/**
 * 机器人状态表
 * 程序会通过这个类给机器人下达指令，策略只需要调用这个类中的 setNewTask 就可以给机器人下达任务
 * 若想取消或中止任务，就调用 setTaskFinished
 */
class RobotState {
private:
    // 当前机器人目标工作台, 没有就是 FREE_STATE 0
    int target;
    // 机器人目标操作 0 是 sell，1 是 buy
    int operation;
    // 机器人携带物品种类，没有携带为 FREE_STATE 0;
    int item_type;
    // 机器人要是已经有任务了就为 true，此时不能给机器人下任务
    // 若为 false，就可以给机器人下任务
    bool is_running;
public:
    RobotState();

    /**
     * 这个函数负责给机器人下达新任务
     * @param new_target 目标工作台
     * @param new_operation 到达工作台的工作
     * @param new_item_type 携带物品种类
     * @return 是否下达成功
     */
    bool setNewTask(int new_target, int new_operation, int new_item_type);

    /**
     * 结束或中止任务
     */
    void setTaskFinished();
    int getTarget() const;
    int getOperation() const;
    int getItemType() const;
    bool getIsRunning() const;
};

/**
 * 地图路由表信息
 * 存储工作台是否可达，机器人是否可下达任务，各个工作台之间的代价，机器人到达时刻表
 */
class Router {
private:
    // 工作台位置，索引和种类信息
    static std::vector<WorkshopConstData> *workshop_const_data;
    // 机器人当前任务信息
    static std::vector<RobotState> *robot_states;
    // 路由表，显示各个工作台之间的距离
    static std::vector<std::vector<double>> *distance_table;
    // 机器人决定购买时这个字段显示购买操作大概会发生在哪一帧
    // 如果没有机器人决定买这个东西就会显示 -1
    static std::vector<int> *workshop_buy_timetable;
    // 非 8 - 9 工作台有机器人决定去售卖时就会显示这个机器人到达会大概在哪一帧
    // 没有机器人决定去那边售卖时就显示 -1
    static std::vector<SellTimeTable> *workshop_sell_timetable;

public:

    Router();

    static std::vector<WorkshopConstData>& getWorkshopConstData();

    static std::vector<RobotState>& getRobotStates();

    static std::vector<std::vector<double>>& getDistanceTable();

    static std::vector<int>& getWorkshopBuyFrame();
};


#endif //HUAWEICONTEST_ROUTER_H
