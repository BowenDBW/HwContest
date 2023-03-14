//
// Created by bowen on 23-3-13.
//

#ifndef HUAWEICONTEST_HUAWEI_IO_H
#define HUAWEICONTEST_HUAWEI_IO_H

#include "data_form.hpp"
#include "game_map.h"

#include <iostream>

namespace HuaweiIO {
    /**
     * 这个方法用于将读取的帧转为 InputFrame 类并返回
     * @return 封装后的一帧
     */
    InputFrame& genFrame();

    /**
     * 发送
     * @param frame
     */
    void sendCommand(const OutputFrame& frame);

    /**
     * 初始化地图的方法
     * @return 初始化完成，返回 true
     */
    bool initMap();
};


#endif //HUAWEICONTEST_HUAWEI_IO_H
