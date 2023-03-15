//
// Created by bowen on 23-3-14.
//

#ifndef HUAWEICONTEST_NAVIGATION_H
#define HUAWEICONTEST_NAVIGATION_H

#include "data_form.hpp"
#include "router.h"

/**
 * 这个类用于对 Router 中机器人任务进行处理并生成输出指令集合 OutputFrame
 */
class Navigation {
private:
    // 当前机器人目标
    int robot_targets[4]{};
    // 当前机器人朝向
    double robots_toward[4]{};
    // 当前机器人携带的物品种类
    int item_types[4]{};
    // 当前机器人执行操作
    int robot_operations[4]{};
    // 当前机器人位置坐标
    Point2D *robot_positions[4]{};
    // 工作台位置与种类信息
    std::vector<WorkshopConstData> targets_data = Router::getWorkshopConstData();
    // 机器人最新所有状态信息
    const std::vector<Robot> *ROBOTS_PROPERTIES =
            GameMap::getFrameBySerial(GameMap::getLatestTimeStamp()).robots;
public:
    Navigation();
    OutputFrame& genCommands();
};


#endif //HUAWEICONTEST_NAVIGATION_H
