//
// Created by bowen on 23-3-13.
//

#include "huawei_io.h"

InputFrame& HuaweiIO::genFrame() {

    std::string string_receiver;
    double float_receiver;
    int int_receiver;
    auto *frame = new InputFrame();
    std::cin >> int_receiver;
    frame->timestamp = int_receiver;

    // 读到 EOF 直接返回该帧
    if(frame->timestamp == EOF){
        return *frame;
    } else {
        // 第一行金钱
        std::cin >> int_receiver;
        frame->budget = int_receiver;

        // 第二行表示场上机器数
        std::cin >> int_receiver;
        frame->workshop_count = int_receiver;

        // 读入机器信息
        for (int i = 0; i < frame->workshop_count; ++i) {
            auto* workshop = new Workshop();
            // 工作台类型
            std::cin >> int_receiver;
            workshop->type = int_receiver;
            // 坐标
            double x;
            double y;
            std::cin >> x >> y;
            workshop->position = new Point2D(x, y);
            // 剩余生产时间
            std::cin >> int_receiver;
            workshop->waiting_time = int_receiver;
            // 原材料状态
            std::cin >> int_receiver;
            workshop->material = int_receiver;
            // 产品格状态
            std::cin >> int_receiver;
            workshop->hasProduct = int_receiver;
            // 加入帧中
            frame->workshops->push_back(*workshop);
        }

        // 读取机器人位置
        for (int i = 0; i < 4; ++i) {
            auto *robot = new Robot();
            // 机器人ID
            robot->id = i;
            // 机器人所处工作台 ID
            std::cin >> int_receiver;
            robot->at_workshop = int_receiver;
            // 携带物品类型
            std::cin >> int_receiver;
            robot->product_type = int_receiver;
            // 时间价值系数
            std::cin >> float_receiver;
            robot->time_param = float_receiver;
            // 碰撞价值系数
            std::cin >> float_receiver;
            robot->collision_param = float_receiver;
            // 角速度
            std::cin >> float_receiver;
            robot->angular_velocity = float_receiver;
            // 线速度
            double x;
            double y;
            std::cin >> x >> y;
            robot->linear_velocity = new Point2D(x, y);
            // 朝向
            std::cin >> float_receiver;
            robot->toward_direction = float_receiver;
            // 坐标
            std::cin >> x >> y;
            robot->position = new Point2D(x, y);
            // 加入帧中
            frame->robots->push_back(*robot);
        }
    }

    std::cin >> string_receiver;
    return *frame;
}

void HuaweiIO::sendCommand(const OutputFrame& frame) {
    std::cout << Map::getLatestTimeStamp() << std::endl;
    std::map<int, double>::iterator iter;
    for(auto &pair : frame.forward) {
        std::cout << "forward " << iter->first << " " << iter->second << std::endl;
    }
    // TODO: 写完剩下的指令
}

bool HuaweiIO::initMap() {
    auto* first_frame = new InputFrame();
    first_frame->workshops = new std::vector<Workshop>;
    first_frame->robots = new std::vector<Robot>();

    char line[100];
    int count = 0;
    while (fgets(line, sizeof line, stdin)) {
        // 读到 OK 返回
        if (line[0] == 'O' && line[1] == 'K') {
            return true;
        }
        // 读到工作台信息保存记录
        for(int i = 0; i < 100; i++) {
            if(line[i] >= 49 && line[i] <= 57) {
                auto* workshop = new Workshop();
                workshop->position = new Point2D(count, i);
                workshop->type = line[i] - '0';
                first_frame->workshops->push_back(*workshop);
                continue;
            }
            if (line[i] == 'A'){
                auto* robot = new Robot();
                robot->position = new Point2D(count, i);
                first_frame->robots->push_back(*robot);
            }
        }
        count ++;
    }
    return false;
}
