//
// Created by bowen on 23-3-15.
//

#include "router.h"

std::vector<std::vector<double>> *Router::distance_table = new std::vector<std::vector<double>>();
std::vector<WorkshopConstData> *Router::workshop_const_data = new std::vector<WorkshopConstData>();
std::vector<RobotState> *Router::robot_states = new std::vector<RobotState>();
std::vector<int> *workshop_buy_frame = new std::vector<int>();
std::map<int, int> *workshop_sell_frame = new std::map<int, int>();

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
        auto *const_data =
                new WorkshopConstData(frame.workshops->at(i).position,
                                      frame.workshops->at(i).type);

        workshop_const_data->push_back(*const_data);
    }

    // 初始化机器人信息
    for (int i = 0; i < 4; ++i) {
        auto *robot_state = new RobotState();
        robot_states->push_back(*robot_state);
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

    // 初始化购买时刻表
    for (int i = 0; i < frame.workshop_count; ++i) {
        workshop_buy_frame->push_back(-1);
    }

    // 初始化销售时刻表
    for (int i = 0; i < frame.workshop_count; ++i) {
        int type = workshop_const_data->at(i).getType();
        if(type == 3){

        }
    }
}

RobotState::RobotState() {
    this->target = 0;
    this->operation = 0;
    this->is_running = false;
    this->item_type = 0;
}

int RobotState::getTarget(){
    return target;
}

int RobotState::getOperation(){
    return operation;
}

int RobotState::getItemType(){
    return item_type;
}

bool RobotState::getIsRunning(){
    return is_running;
}

bool RobotState::setNewTask(int new_target, int new_operation, int new_item_type) {
    if(is_running){
        return false;
    } else {
        target = new_target;
        item_type = new_operation;
        operation = new_item_type;
        is_running = true;
    }
}

void RobotState::setTaskFinished() {
    is_running = false;
}

Point2D& WorkshopConstData::getPosition() {
    return *point;
}

int WorkshopConstData::getType() {
    return type;
}

WorkshopConstData::WorkshopConstData(Point2D* point, int type) {
    this->type = type;
    this->point = point;
}
