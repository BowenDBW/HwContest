//
// Created by bowen on 23-3-16.
//

#include "planning_simple.h"

[[noreturn]]void SimplePlanning::planningLoop() {
    while(true){
        for (int i = 0; i < 4; ++i) {
            std::vector<WorkshopConstData> datas = Router::getWorkshopConstData();
            if(Router::getRobotStates().at(i).getIsRunning()){
                continue;
            }else if(Router::getRobotStates().at(i).getItemType() == FREE_STATE){
                int best_target = FREE_STATE;
                double nearest_distance = UNLOCK;
                for(int j = 0; j < datas.size(); ++j){
                    if(datas[j].getType() > 7 || Router::getWorkshopBuyTimetable()[i] != UNLOCK){
                        continue;
                    } else {
                        if(Router::getRobotStates().at(i).getTarget() == FREE_STATE){
                            Point2D robot_final =Router::getRobotStates().at(i).getFinalPosition();
                            Point2D target_pos = datas[j].getPosition();
                            double distance = sqrt(pow(robot_final.x - target_pos.x, 2)
                                    + pow(robot_final.y - target_pos.y, 2));
                            if(nearest_distance == UNLOCK){
                                nearest_distance = distance;
                                best_target = j;
                            } else {
                                if(distance < nearest_distance){
                                    nearest_distance = distance;
                                    best_target = j;
                                }
                            }
                        } else {
                            double distance = Router::getDistanceTable()[Router::getRobotStates().at(i).getTarget()][j];
                            if (distance == NOT_REACHABLE){
                                continue;
                            } else {
                                if(nearest_distance == UNLOCK){
                                    nearest_distance = distance;
                                    best_target = j;
                                } else {
                                    if(distance < nearest_distance){
                                        nearest_distance = distance;
                                        best_target = j;
                                    }
                                }
                            }
                        }
                    }
                }
                Router::getRobotStates().at(i).setNewTask(best_target, RobotState::BUY);
                //is_running = false;

            }else{

                int best_target = FREE_STATE;
                double nearest_distance = UNLOCK;
                for(int j = 0; j < datas.size(); ++j){
                    if(datas[j].getType() != 9){
                        continue;
                    } else {
                        if(Router::getRobotStates().at(i).getTarget() == FREE_STATE){
                            Point2D robot_final =Router::getRobotStates().at(i).getFinalPosition();
                            Point2D target_pos = datas[j].getPosition();
                            double distance = sqrt(pow(robot_final.x - target_pos.x, 2)
                                                   + pow(robot_final.y - target_pos.y, 2));
                            if(nearest_distance == UNLOCK){
                                nearest_distance = distance;
                                best_target = j;
                            } else {
                                if(distance < nearest_distance){
                                    nearest_distance = distance;
                                    best_target = j;
                                }
                            }
                        } else {
                            double distance = Router::getDistanceTable()[Router::getRobotStates().at(i).getTarget()][j];
                            if (distance == NOT_REACHABLE){
                                continue;
                            } else {
                                if(nearest_distance == UNLOCK){
                                    nearest_distance = distance;
                                    best_target = j;
                                } else {
                                    if(distance < nearest_distance){
                                        nearest_distance = distance;
                                        best_target = j;
                                    }
                                }
                            }
                        }
                    }
                }

                std::cout << "分配了销售任务" << std::endl;
                Router::getRobotStates().at(i).setNewTask(best_target, RobotState::SELL);
            }
        }
    }
}
