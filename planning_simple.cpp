//
// Created by bowen on 23-3-16.
//

#include "planning_simple.h"

[[noreturn]]void SimplePlanning::planningLoop() {
    while(true){
        for (int i = 0; i < 4; ++i) {
            RobotState state = Router::getRobotStates().at(i);
            if(state.getIsRunning()){
                continue;
            }else if(state.getItemType() == FREE_STATE){

            }else{

            }
        }
    }
}
