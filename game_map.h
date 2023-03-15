//
// Created by bowen on 23-3-15.
//

#ifndef HUAWEICONTEST_GAME_MAP_H
#define HUAWEICONTEST_GAME_MAP_H

#include "data_form.hpp"
#include <iostream>
#include <vector>

class GameMap {
private:
    // 当前帧
    static int latest_timestamp;
    // 地图中的工作台信息
    static std::vector<InputFrame> *map_frames;

public:
    static int getLatestTimeStamp();

    static std::vector<InputFrame>& getMapFrames();

    static InputFrame getFrameBySerial(const int serial);

    static InputFrame getFrameBySerial(const int serial, const int search_start_frame);

    static void updateFrame(int new_timestamp, const InputFrame& map_frame);
};

#endif //HUAWEICONTEST_GAME_MAP_H
