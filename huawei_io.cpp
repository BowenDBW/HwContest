//
// Created by bowen on 23-3-13.
//

#include "huawei_io.h"

/**
 * 这个方法用于将读取的帧转为 InputFrame 类并返回
 * @return 封装后的一帧
 */
InputFrame* HuaweiIO::genFrame() {
    std::string receiver;
    auto *frame = new InputFrame();
    frame->timestamp = atoi(receiver.c_str());
    // 读到 EOF 直接返回该帧
    if(frame->timestamp == EOF){
        return frame;
    } else {
        // TODO：处理输入帧
    }
}

void HuaweiIO::sendCommand(const OutputFrame& frame) {

}

/**
 * 初始化地图的方法
 * @return 初始化完成，返回 true
 */
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
