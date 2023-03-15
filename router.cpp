//
// Created by bowen on 23-3-15.
//

#include "router.h"

std::vector<std::vector<double>> *Router::distance_table = new std::vector<std::vector<double>>();
std::vector<WorkshopConstData> *Router::workshop_const_data = new std::vector<WorkshopConstData>();
std::vector<RobotState> *Router::robot_states = new std::vector<RobotState>();
std::vector<int> *Router::workshop_buy_timetable = new std::vector<int>();
std::vector<SellTimeTable> *Router::workshop_sell_timetable = new std::vector<SellTimeTable>();

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
        workshop_buy_timetable->push_back(UNLOCK);
    }

    // 初始化销售时刻表
    for (int i = 0; i < frame.workshop_count; ++i) {
        int type = workshop_const_data->at(i).getType();
        if(type == 4){
            SellTimeTable table1{};
            table1.material_type = 1;
            table1.index = i;
            table1.arrival_frame = UNLOCK;
            workshop_sell_timetable->push_back(table1);
            SellTimeTable table2{};
            table2.material_type = 2;
            table2.index = i;
            table2.arrival_frame = UNLOCK;
            workshop_sell_timetable->push_back(table2);
        }
        if(type == 5){
            SellTimeTable table1{};
            table1.material_type = 1;
            table1.index = i;
            table1.arrival_frame = UNLOCK;
            workshop_sell_timetable->push_back(table1);
            SellTimeTable table2{};
            table2.material_type = 3;
            table2.index = i;
            table2.arrival_frame = UNLOCK;
            workshop_sell_timetable->push_back(table2);
        }
        if(type == 6){
            SellTimeTable table1{};
            table1.material_type = 2;
            table1.index = i;
            table1.arrival_frame = UNLOCK;
            workshop_sell_timetable->push_back(table1);
            SellTimeTable table2{};
            table2.material_type = 3;
            table2.index = i;
            table2.arrival_frame = UNLOCK;
            workshop_sell_timetable->push_back(table2);
        }
        if(type == 7) {
            SellTimeTable table1{};
            table1.material_type = 4;
            table1.index = i;
            table1.arrival_frame = UNLOCK;
            workshop_sell_timetable->push_back(table1);
            SellTimeTable table2{};
            table2.material_type = 5;
            table2.index = i;
            table2.arrival_frame = UNLOCK;
            workshop_sell_timetable->push_back(table2);
            SellTimeTable table3{};
            table3.material_type = 6;
            table3.index = i;
            table3.arrival_frame = UNLOCK;
            workshop_sell_timetable->push_back(table3);
        }
    }
}

std::vector<WorkshopConstData> &Router::getWorkshopConstData() {
    return *workshop_const_data;
}

std::vector<RobotState> &Router::getRobotStates() {
    return *robot_states;
}

std::vector<std::vector<double>> &Router::getDistanceTable() {
    return *distance_table;
}

std::vector<int> &Router::getWorkshopBuyFrame() {
    return *workshop_buy_timetable;
}

RobotState::RobotState() {
    this->target = 0;
    this->operation = 0;
    this->is_running = false;
    this->item_type = 0;
}

int RobotState::getTarget() const{
    return target;
}

int RobotState::getOperation() const{
    return operation;
}

int RobotState::getItemType() const{
    return item_type;
}

bool RobotState::getIsRunning() const{
    return is_running;
}

bool RobotState::setNewTask(int new_target, int new_operation, int new_item_type) {
    if(is_running){
        return false;
    }
    target = new_target;
    item_type = new_operation;
    operation = new_item_type;
    is_running = true;
    return true;
}

void RobotState::setTaskFinished() {
    is_running = false;
}

Point2D& WorkshopConstData::getPosition() {
    return *point;
}

int WorkshopConstData::getType() const {
    return type;
}

WorkshopConstData::WorkshopConstData(Point2D* point, int type) {
    this->type = type;
    this->point = point;
}
