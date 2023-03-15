//
// Created by 26317 on 2023/3/13.
//

#include "huawei_io.h"
#include "game_map.h"
#include <thread>

bool reach_end = false;
int stamp_record = -2;

[[noreturn]] void inputListener();
void startGame();

int main(){
    startGame();
}

/**
 * 输入监听器，每当其收到系统的输入时就将其转化为一个帧对象并加入结果中
 */
[[noreturn]] void inputListener(){
    while (true) {
        InputFrame frame = HuaweiIO::genFrame();
        // 读到末尾程序结束
        if(frame.timestamp == EOF){
            reach_end = true;
        } else {
            GameMap::updateFrame(frame.timestamp, frame);
        }
    }
}

/**
 * 程序主循环
 */
void startGame(){
    // 初始化地图
    HuaweiIO::initMap();
    std::cout << "OK" << std::endl;

    // 输入监听器
    std::thread in_stream_thread(inputListener);
    in_stream_thread.detach();

    // 算法输出主进程
    while(!reach_end) {
        // 时间戳一致时不处理，时间戳为0时不处理
        if (stamp_record == GameMap::getLatestTimeStamp() || GameMap::getLatestTimeStamp() == 0) {
            continue;
        }
        stamp_record = GameMap::getLatestTimeStamp();

        OutputFrame outputFrame;
        outputFrame.forward->insert(std::pair<int, double>(1,2.0));
        //TODO: 主进程，用于添加算法

        // 输出结果线程
        std::thread out_stream_thread(HuaweiIO::sendCommand, outputFrame);
        out_stream_thread.detach();
    }
}