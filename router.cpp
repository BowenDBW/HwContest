//
// Created by bowen on 23-3-15.
//

#include "router.h"

std::vector<std::vector<double>> *Router::distance_table = new std::vector<std::vector<double>>();
std::vector<WorkshopConstData> *Router::workshop_const_data = new std::vector<WorkshopConstData>();
std::vector<RobotState> *Router::robot_states = new std::vector<RobotState>();

Router::Router() {
    // 获取第一帧
    while (true){
        if(GameMap::getLatestTimeStamp() >= 1){
            break;
        }
    }
    InputFrame frame = GameMap::getFrameBySerial(1);

    // 初始化工作台信息
    for (int i = 0; i < frame.workshop_count; ++i) {
        auto *const_data = new WorkshopConstData();
        const_data->type = frame.workshops->at(i).type;
        const_data->point = frame.workshops->at(i).position;
        workshop_const_data->push_back(*const_data);
    }

    // 初始化路由表
    for (int i = 0; i < frame.workshop_count; ++i) {
        auto *row = new std::vector<double>();
        for (int j = 0; j < frame.workshop_count; ++j) {
            if (i == j){
                row->push_back(MAXFLOAT);
            }
            double distance;
            Point2D *rowPoint = frame.workshops->at(i).position;
            Point2D *columnPoint = frame.workshops->at(j).position;
            distance = sqrt(pow(rowPoint->x - columnPoint->x, 2)
                    + pow(rowPoint->y - columnPoint->y, 2));
            row->push_back(distance);
        }
        distance_table->push_back(*row);
    }
}
