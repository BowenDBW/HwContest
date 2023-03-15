//
// Created by bowen on 23-3-14.
//

#include "navigation.h"
OutputFrame& Navigation::genCommands(){

    const std::vector<Robot> *ROBOTS_PROPERTIES =
            GameMap::getFrameBySerial(GameMap::getLatestTimeStamp()).robots;

    // 提取导航需要的属性
    int ROBOT_TARGETS[4];
    int ITEM_TYPES[4];
    int ROBOT_OPERATION[4];
    Point2D *ROBOT_POSITIONS[4];
    double ROBOT_TOWARDS[4];
    for (int i = 0; i < 4; ++i) {
        ROBOT_TARGETS[i] = Router::getRobotStates().at(i).getTarget();
        ITEM_TYPES[i] = Router::getRobotStates().at(i).getItemType();
        ROBOT_OPERATION[i] = Router::getRobotStates().at(i).getOperation();
        ROBOT_POSITIONS[i] = ROBOTS_PROPERTIES->at(i).position;
        ROBOT_TOWARDS[i] = ROBOTS_PROPERTIES->at(i).toward_direction;
    }

    for (int i = 0; i < 4; ++i) {
        // 如果机器人没有被分配任务，就直接跳到下一个机器人
        if(!Router::getRobotStates().at(i).getIsRunning()){
            continue;
        }
        // 如果机器人与另一个机器人距离太近，判断是否冲突，
        // 如果冲突且都在执行任务编号小的停止，编号大的绕行，然后直接跳过后续逻辑
        // 暂时不考虑一个机器人没任务的情况


        // 如果机器人角度与目标差距在阈值外，赋予角速度


        // 如果机器人与目标距离大于 0.2 米，赋予线速度，大小跟夹角相关


        // 如果机器人与目标小于 0.2米，进行交易，设置任务完成
    }
}