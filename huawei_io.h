//
// Created by bowen on 23-3-13.
//

#ifndef HUAWEICONTEST_HUAWEI_IO_H
#define HUAWEICONTEST_HUAWEI_IO_H

#include "data_form.hpp"

#include <iostream>

class HuaweiIO {
public:
    static InputFrame* genFrame();

    static void sendCommand(const OutputFrame& frame);

    static bool initMap();
};


#endif //HUAWEICONTEST_HUAWEI_IO_H
