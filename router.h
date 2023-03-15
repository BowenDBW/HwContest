//
// Created by bowen on 23-3-15.
//

#ifndef HUAWEICONTEST_ROUTER_H
#define HUAWEICONTEST_ROUTER_H

#include "game_map.h"

#include <vector>
#include <cmath>

class WorkshopConstData {
private:
    Point2D *point{};
    int type;
public:
    WorkshopConstData(Point2D* point, int type);
    Point2D& getPosition();
    int getType();
};

class RobotState {
private:
    // 当前机器人目标工作台, 没有就是 0
    int target;
    // 机器人目标操作 0 是 sell，1 是 buy
    int operation;
    // 机器人携带物品种类，没有就携带 0;
    int item_type;
    // 机器人要是已经有任务了就为 true，此时不能给机器人下任务
    // 若为 false，就可以给机器人下任务
    bool is_running;
public:
    RobotState();

    void setTaskFinished();

    bool setNewTask(int new_target, int new_operation, int new_item_type);

    int getTarget();

    int getOperation();

    int getItemType();

    bool getIsRunning();
};

class Router {
private:
    struct SellTimeTable{
        int serial;
        int material_type;
        int arrival_frame;
    };
    // 工作台位置，索引和种类信息
    static std::vector<WorkshopConstData> *workshop_const_data;
    // 机器人当前任务信息
    static std::vector<RobotState> *robot_states;
    // 路由表，显示各个工作台之间的距离
    static std::vector<std::vector<double>> *distance_table;
    // 机器人决定购买时这个字段显示购买操作大概会发生在哪一帧
    // 如果没有机器人决定买这个东西就会显示 -1
    static std::vector<int> *workshop_buy_frame;
    // 非 8 - 9 工作台有机器人决定去售卖时就会显示这个机器人到达会大概在哪一帧
    // 没有机器人决定去那边售卖时就显示 -1
    static SellTimeTable *workshop_sell_frame;

public:

    Router();

    static std::vector<WorkshopConstData>& getWorkshopConstData();

    static std::vector<RobotState>& getRobotStates();

    static std::vector<std::vector<double>>& getDistanceTable();

    static std::vector<int>& getWorkshopBuyFrame();
};


#endif //HUAWEICONTEST_ROUTER_H
