//
// Created by bowen on 23-3-16.
//

#include "planning_simple.h"

[[noreturn]]void SimplePlanning::planningLoop() {
    while(true){
        for (int i = 0; i < 4; ++i) {
            RobotState state = Router::getRobotStates().at(i);
            std::vector<WorkshopConstData> datas = Router::getWorkshopConstData();
            if(state.getIsRunning()){
                continue;
            }else if(state.getItemType() == FREE_STATE){
                int best_target = FREE_STATE;
                double nearest_distance = UNLOCK;
                for(int j = 0; j < Router::getWorkshopCount(); ++j){
                    if(datas[j].getType() > 7 || Router::getWorkshopBuyTimetable()[i] != UNLOCK){
                        continue;
                    } else {
                        if(state.getTarget() == FREE_STATE){
                            Point2D robot_final =state.getFinalPosition();
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
                            double distance = Router::getDistanceTable()[state.getTarget()][j];
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

                state.setNewTask(best_target, RobotState::BUY);

            }else{

                int best_target = FREE_STATE;
                double nearest_distance = UNLOCK;
                for(int j = 0; j < Router::getWorkshopCount(); ++j){
                    if(datas[j].getType() != 9){
                        continue;
                    } else {
                        if(state.getTarget() == FREE_STATE){
                            Point2D robot_final =state.getFinalPosition();
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
                            double distance = Router::getDistanceTable()[state.getTarget()][j];
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

                state.setNewTask(best_target, RobotState::SELL);
            }
        }
    }
}
