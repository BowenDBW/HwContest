//
// Created by chenhong on 2023/3/16.
//

#ifndef HUAWEICONTEST_PLANNING_BEHAVIORTREE_H
#define HUAWEICONTEST_PLANNING_BEHAVIORTREE_H

#include "planning.h"

class PlanningBehavior : public Planning{
public:
    [[noreturn]]void planningLoop() override;
};

#endif //HUAWEICONTEST_PLANNING_BEHAVIORTREE_H
