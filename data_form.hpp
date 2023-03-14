//
// Created by bowen on 23-3-13.
//

#ifndef HUAWEICONTEST_DATA_FORM_HPP
#define HUAWEICONTEST_DATA_FORM_HPP

#include <vector>
#include <map>


struct Point2D{
    double x;
    double y;
};


struct Workshop {
    // 工作台类型
    int type;
    // 工作台坐标
    Point2D position;
    // 剩余生产时间
    // -1 表示没有生产
    // 0 表示生产因输出格满而阻塞
    int waiting_time;
    // 产品格状态
    bool hasProduct;
};

struct Robot {
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
    Point2D linear_velocity;
    // 朝向
    double toward_direction;
    // 坐标
    Point2D position;
};

struct Map {
    // 当前帧
    int time_stamp;
    // 地图中的工作台信息
    static std::vector<Workshop> workshops;
    // 地图中的机器人信息
    static std::vector<Robot> robots;
};

struct InputFrame {
    // 帧序号
    int serial;
    // 金钱数
    int budget;
    // 工作台数量
    int workshop_count;
    // 工作台属性
    std::vector<Workshop> workshops;
    // 机器人属性
    std::vector<Robot> robots;
};

struct OutputFrame {
    // 设置前进速度
    std::map<int, double> forward;
    // 设置旋转速度
    std::map<int, double> rotate;
    // 该帧购买操作机器人ID
    std::vector<int> buy;
    // 该帧销售操作机器人ID
    std::vector<int> sell;
    // 该帧销毁操作机器人ID
    std::vector<int> destroy;
};


#endif //HUAWEICONTEST_DATA_FORM_HPP
