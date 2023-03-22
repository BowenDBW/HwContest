//
// Created by bowen on 23-3-15.
//

#include "router.h"

std::vector<std::vector<double>> *Router::distance_table = new std::vector<std::vector<double>>();
std::vector<WorkshopConstData> *Router::workshop_const_data = new std::vector<WorkshopConstData>();
std::vector<RobotState> *Router::robot_states = new std::vector<RobotState>();
std::vector<int> *Router::workshop_buy_timetable = new std::vector<int>();
std::vector<SellTimeTable> *Router::workshop_sell_timetable = new std::vector<SellTimeTable>();
int Router::workshop_count = FREE_STATE;

Router::Router() {
    // 获取第一帧
    while (true){
        if(GameMap::getLatestTimeStamp() >= 1){
            break;
        }
    }

    InputFrame frame = GameMap::getFrameBySerial(1);
    workshop_count = frame.workshop_count;

    // 初始化工作台信息
    for (int i = 0; i < workshop_count; ++i) {
        auto *const_data =
                new WorkshopConstData(frame.workshops->at(i).position,
                                      frame.workshops->at(i).type);

        workshop_const_data->push_back(*const_data);
    }

    // 初始化机器人信息
    for (int i = 0; i < 4; ++i) {
        auto *robot_state = new RobotState(GameMap::getLatestFrame().robots->at(1).position);
        robot_states->push_back(*robot_state);
    }

    // 初始化路由表
    for (int i = 0; i < frame.workshop_count; ++i) {
        auto *row = new std::vector<double>();
        for (int j = 0; j < frame.workshop_count; ++j) {
            if (i == j){
                row->push_back(NOT_REACHABLE);
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

std::vector<WorkshopConstData> &Router::getWorkshopByType(int type) {
    auto* ones = new std::vector<WorkshopConstData>();
    for(WorkshopConstData data : *workshop_const_data){
        if (data.getType() == type){
            ones->push_back(data);
        }
    }
    return *ones;
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

std::vector<int> &Router::getWorkshopBuyTimetable() {
    return *workshop_buy_timetable;
}

std::vector<SellTimeTable> &Router::getWorkshopSellTimetable() {
    return *workshop_sell_timetable;
}

SellTimeTable Router::getSellTimeTableByIndexAndMaterial(int index, int material_type) {
    for(SellTimeTable table : *workshop_sell_timetable){
        if(table.index == index && table.material_type == material_type){
            return table;
        }
    }
    throw std::invalid_argument(&"no matched index or material type "
                                 "in function getSellTimeTableByIndexAndMaterial:" [index]);
}

bool Router::updateSellTimeTable(int index, int material_type, int arrival_frame) {
    for(SellTimeTable table : *workshop_sell_timetable){
        if(table.index == index && table.material_type == material_type){
            table.arrival_frame = arrival_frame;
            return true;
        }
    }
    throw std::invalid_argument(&"no matched index or material type "
                                 "in function updateSellTimeTable:" [index]);
}

int Router::getWorkshopCount() {
    return workshop_count;
}


RobotState::RobotState(Point2D *point2D) {
    this->final_position = point2D;
    this->target = FREE_STATE;
    this->operation = FREE_STATE;
    this->is_running = false;
    this->item_type = FREE_STATE;
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

bool RobotState::setNewTask(int new_target, int new_operation) {
    if(is_running){
        return false;
    }

    // 计算预估到达时间
    Point2D position_now = Router::getWorkshopConstData().at(target).getPosition();
    Point2D position_next = Router::getWorkshopConstData().at(new_target).getPosition();
    double distance = sqrt(pow(position_now.x - position_next.x, 2)
                           + pow(position_now.y - position_next.y, 2));
    // 暂且设置阈值为 100 (2秒)
    int time_estimate = GameMap::getLatestTimeStamp() + (int)distance / (int)Robot::MAX_FORWARD + 100;

    // 更新时刻表
    if(new_operation == SELL){
        Router::updateSellTimeTable(new_target, item_type,time_estimate);
    } else if (new_operation == BUY){
        Router::getWorkshopBuyTimetable()[new_target] = time_estimate;
    } else{
        throw std::invalid_argument(&"operation in function setNewTask received:" [new_operation]);
    }
    // 改变状态
    // 赋值
    operation = new_operation;
    target = new_target;
    is_running = true;
    return true;
}

void RobotState::setTaskFinished(Point2D *point2D) {
    // 更新时刻表
    if(operation == SELL){
        item_type = FREE_STATE;
        Router::updateSellTimeTable(target, item_type,UNLOCK);
    } else if (operation == BUY){
        item_type = Router::getWorkshopConstData().at(target).getType();
        Router::getWorkshopBuyTimetable()[target] = UNLOCK;
    } else{
        throw std::invalid_argument(&"operation in function setTaskFinished received:" [ operation]);
    }
    // 改变状态
    is_running = false;
}

Point2D &RobotState::getFinalPosition() const {
    return *final_position;
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
