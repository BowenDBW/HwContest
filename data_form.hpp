//
// Created by bowen on 23-3-13.
//

#ifndef HUAWEICONTEST_DATA_FORM_HPP
#define HUAWEICONTEST_DATA_FORM_HPP

#include <vector>
#include <map>
#include <cmath>

struct Point2D {
    double x;
    double y;

    Point2D(double x, double y){
        this->x = x;
        this->y = y;
    }
};

struct WorkshopProperties{
    const int PRE_STEP[7][3] = {
            0,0,0,
            0,0,0,
            0,0,0,
            1,2,0,
            1,3,0,
            2,3,0,
            4,5,6,
    };
    const double MONEY_COST[7] = {
            3000,
            4400,
            5800,
            15400,
            17200,
            19200,
            76000
    };
    const double MONEY_EARN[7] = {
            6000,
            7600,
            9200,
            22500,
            25000,
            27500,
            105000
    };
    const int TIME_COST[7] = {
            50,
            50,
            50,
            500,
            500,
            500,
            1000,
    };
};

struct Workshop {
    int id{};
    // 工作台类型
    int type{};
    // 工作台坐标
    Point2D *position{};
    // 剩余生产时间
    // -1 表示没有生产
    // 0 表示生产因输出格满而阻塞
    int waiting_time{};
    // 原材料格状态
    std::vector<int> *material = new std::vector<int>();
    // 产品格状态
    bool hasProduct{};
};

struct Robot {
    // 最大前进速度
    static constexpr double MAX_FORWARD = 6;
    // 最大倒退速度
    static constexpr double MAX_BACKWARD = -2;
    // 最大旋转速度
    static constexpr double MAX_ROTATE_SPEED = M_PI;
    // 最大牵牵引力
    static constexpr double MAX_TRACTION = 250;
    // 最大力矩
    static constexpr double MAX_TORQUE = 50;
    // 机器人 id
    int id;
    // 当前处于的工作台编号，
    // -1 代表没有
    // 工作台编号 0 ~ (n - 1)
    int at_workshop;
    // 携带物品类型
    // 0 表示没有携带物品
    // 1-7 代表携带 1-7 中的一种
    int product_type;
    // 时间价值系数
    double time_param;
    // 碰撞价值系数
    double collision_param;
    // 角速度
    double angular_velocity;
    // 线速度
    Point2D* linear_velocity;
    // 朝向
    double toward_direction;
    // 坐标
    Point2D* position;
};

struct InputFrame {
    // 帧序号
    int timestamp{};
    // 金钱数
    int budget{};
    // 工作台数量
    int workshop_count{};
    // 工作台属性
    std::vector<Workshop> *workshops = new std::vector<Workshop>();
    // 机器人属性
    std::vector<Robot> *robots = new std::vector<Robot>();
};

struct OutputFrame {
    // 设置前进速度
    std::map<int, double> *forward = new std::map<int, double>();
    // 设置旋转速度
    std::map<int, double> *rotate = new std::map<int, double>();
    // 该帧购买操作机器人ID
    std::vector<int> *buy = new std::vector<int>();
    // 该帧销售操作机器人ID
    std::vector<int> *sell = new std::vector<int>();
    // 该帧销毁操作机器人ID
    std::vector<int> *destroy = new std::vector<int>();
};

#endif //HUAWEICONTEST_DATA_FORM_HPP
