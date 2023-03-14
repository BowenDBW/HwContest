//
// Created by 26317 on 2023/3/13.
//
#include "huawei_io.h"

#include <thread>

bool reach_end = false;

[[noreturn]] bool inputListener(){
    while (true) {
        InputFrame *frame = HuaweiIO::genFrame();
        // 读到末尾程序结束
        if(frame->timestamp == EOF){
            reach_end =  true;
        } else {
            Map::updateFrame(frame->timestamp, *frame);
        }
    }
}

int main(){
    // 初始化地图
    HuaweiIO::initMap();
    std::cout << "OK";

    std::thread in_stream_thread(inputListener);
    in_stream_thread.detach();

    while(!reach_end){
        OutputFrame outputFrame;
        //TODO: 主线程，用于添加算法
        HuaweiIO::sendCommand(outputFrame);
    }
}