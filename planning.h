//
// Created by bowen on 23-3-14.
//

#ifndef HUAWEICONTEST_PLANNING_H
#define HUAWEICONTEST_PLANNING_H


class RobotPlan {
private:
    //目标购买工作台
    int nextBuyStation;
    //目标售卖工作台
    int nextSaleStation;

public:
    RobotPlan();
    //计算从一个工作周期的时间耗费和收入情况
    double calculationIncome();
    //计算单位时间最高收益
    double incomePerFrame();

};


#endif //HUAWEICONTEST_PLANNING_H
