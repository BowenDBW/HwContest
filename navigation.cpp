//
// Created by bowen on 23-3-14.
//
#include "navigation.h"

Navigation::Navigation() {
    targets_data = Router::getWorkshopConstData();
    for (int i = 0; i < 4; ++i) {
        robot_targets[i] = Router::getRobotStates().at(i).getTarget();
        item_types[i] = Router::getRobotStates().at(i).getItemType();
        robot_operations[i] = Router::getRobotStates().at(i).getOperation();
        robot_positions[i] = ROBOTS_PROPERTIES->at(i).position;
        robots_toward[i] = ROBOTS_PROPERTIES->at(i).toward_direction;
    }
}

OutputFrame& Navigation::genCommands(){
    auto* frame = new OutputFrame();
    for (int i = 0; i < 4; ++i) {
        // 如果机器人没有被分配任务，就直接跳到下一个机器人
        if (!Router::getRobotStates().at(i).getIsRunning()) {
            continue;
        }
        // 相对距离
        const double DISTANCE = sqrt(pow(robot_positions[i]->x - targets_data.at(robot_targets[i]).getPosition().x, 2)
                                     +
                                     pow(robot_positions[i]->y - targets_data.at(robot_targets[i]).getPosition().y, 2));
        // 机器人应该前进的方向
        const double TRUE_TOWARDS = atan2(robot_positions[i]->y - targets_data.at(robot_targets[i]).getPosition().y,
                                           robot_positions[i]->x - targets_data.at(robot_targets[i]).getPosition().x);
        // 机器人朝向与前进方向的差：实际 - 朝向;
        // 范围 [-pi,pi];
        // 相对左边 > 0, 顺时针转; 相对右边 < 0;
        double differ_of_angle = robots_toward[i] - TRUE_TOWARDS;
        if(differ_of_angle > M_PI){
            differ_of_angle -= M_PI;
        }

        if(differ_of_angle < - M_PI){
            differ_of_angle += M_PI;
        }

        // 如果机器人与另一个机器人距离太近，判断是否冲突，
        // 如果冲突且都在执行任务编号小的停止，编号大的绕行，然后直接跳过后续逻辑
        // 暂时不考虑一个机器人没任务的情况
        //TODO:避障策略

        // 如果机器人角度与目标差距在阈值外，赋予角速度
        // 满速旋转 1 帧 0.0628(3.6度)
        // 减速阈值 0.08 (5度)，减速后依据角度差逐渐减小速度
        // 衰减系数
        // 停转阈值 0.0035（0.2度）
        const double MAX_ROTATE_SPEED_THRESHOLD = 0.08;
        const double STOP_ROTATE_THRESHOLD = 0.004;
        const double DECLINE_RATE = 2;
        if(differ_of_angle >= MAX_ROTATE_SPEED_THRESHOLD){
            frame->insertRotate(i, Robot::MAX_ROTATE_SPEED);
        } else if(differ_of_angle <= -MAX_ROTATE_SPEED_THRESHOLD){
            frame->insertRotate(i, -Robot::MAX_ROTATE_SPEED);
        } else if(differ_of_angle <= MAX_ROTATE_SPEED_THRESHOLD || differ_of_angle >= STOP_ROTATE_THRESHOLD){
            frame->insertRotate(i, Robot::MAX_ROTATE_SPEED * exp(-differ_of_angle * DECLINE_RATE));
        } else if(differ_of_angle >= -MAX_ROTATE_SPEED_THRESHOLD || differ_of_angle <= - STOP_ROTATE_THRESHOLD){
            frame->insertRotate(i, -Robot::MAX_ROTATE_SPEED * exp(-differ_of_angle * DECLINE_RATE));
        } else {
            frame->insertRotate(i, 0);
        }

        // 如果机器人与目标距离大于 0.2 米，赋予线速度，大小跟夹角相关
        if(std::abs(differ_of_angle) >= (M_PI / 2)){
            frame->insertForward(i, 0);
        } else if(std::abs(differ_of_angle) < (M_PI / 2) || std::abs(differ_of_angle) > STOP_ROTATE_THRESHOLD){
            frame->insertForward(i, Robot::MAX_FORWARD * ((M_PI / 2 - differ_of_angle) / (M_PI / 2)));
        } else {
            frame->insertForward(i, Robot::MAX_FORWARD);
        }

        // 如果机器人与目标小于 0.2米，进行交易，设置任务完成
        if(DISTANCE < 0.2){
            if(Router::getRobotStates().at(i).getOperation() == RobotState::BUY){
                frame->buy->push_back(i);
            }
            if(Router::getRobotStates().at(i).getOperation() == RobotState::SELL){
                frame->sell->push_back(i);
            }
            Point2D *final_position = GameMap::getLatestFrame().robots->at(i).position;
            Router::getRobotStates().at(i).setTaskFinished(final_position);
        }
    }
}
