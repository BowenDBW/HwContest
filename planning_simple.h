//
// Created by bowen on 23-3-16.
//

#ifndef HUAWEICONTEST_PLANNING_SIMPLE_H
#define HUAWEICONTEST_PLANNING_SIMPLE_H

#include "planning.h"
#include "router.h"

class SimplePlanning : public Planning{
public:
    [[noreturn]]void planningLoop() override;
};


#endif //HUAWEICONTEST_PLANNING_SIMPLE_H
