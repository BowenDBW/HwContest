//
// Created by 26317 on 2023/3/13.
//

#include "huawei_io.h"
#include "game_map.h"
#include "navigation.h"
#include "planning_simple.h"

#include <thread>

bool reach_end = false;
int stamp_record = -2;

// 这个方法用于启动所有子线程
void initThreads();
// 这个方法用于开启主循环
void startGame();

int main(){
    // 初始化地图
    HuaweiIO::initMap();
    std::cout << "OK" << std::endl;

    // 进入比赛
    initThreads();
    startGame();
}

/**
 * 输入监听器，每当其收到系统的输入时就将其转化为一个帧对象并加入结果中
 */
[[noreturn]] void inputListener(){
    while (true) {
        //读取输入帧
        InputFrame frame = HuaweiIO::genFrame();
        // 读到末尾程序结束
        if(frame.timestamp == EOF){
            reach_end = true;
        } else {
            //更新帧
            GameMap::updateFrame(frame.timestamp, frame);
        }
    }
}

/**
 * 工厂模式，这里选择决策模型
 */
 void planningListener(){
     // 这个地方决定你用什么决策模型
     Planning *planning = new SimplePlanning();
     planning->planningLoop();
 }

/**
 * 初始化函数
 */
void initThreads(){
    // 输入监听器
    std::thread in_stream_thread(inputListener);
    in_stream_thread.detach();

    // 初始化路由表
    new Router();

    // 决策树启动
    std::thread planning_thread(planningListener);
    planning_thread.detach();
}

/**
 * 主进程循环
 */
void startGame(){
    while(!reach_end) {
        // 时间戳一致时不处理，时间戳为0时不处理
        if (stamp_record == GameMap::getLatestTimeStamp() || GameMap::getLatestTimeStamp() == 0) {
            continue;
        }
        stamp_record = GameMap::getLatestTimeStamp();

        // 初始化一个导航类
        auto* navigation = new Navigation();
        OutputFrame outputFrame = navigation->genCommands();;

        // 单独开一个线程输出结果
        std::thread out_stream_thread(HuaweiIO::sendCommand, outputFrame);
        out_stream_thread.detach();

        // 释放导航类
        delete navigation;
    }
}