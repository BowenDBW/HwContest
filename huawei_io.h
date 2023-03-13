//
// Created by bowen on 23-3-13.
//

#ifndef HUAWEICONTEST_HUAWEI_IO_H
#define HUAWEICONTEST_HUAWEI_IO_H

#include "data_form.hpp"
#include <iostream>

class HuaweiIO {
public:
    InputFrame genFrame();

    void sendCommand(const OutputFrame& frame);
};


#endif //HUAWEICONTEST_HUAWEI_IO_H
