//
// Created by bowen on 23-3-15.
//

#include "game_map.h"

int GameMap::latest_timestamp;
std::vector<InputFrame> *GameMap::map_frames = new std::vector<InputFrame>();

int GameMap::getLatestTimeStamp(){
    return latest_timestamp;
}

std::vector<InputFrame>& GameMap::getMapFrames(){
    return *map_frames;
}

void GameMap::updateFrame(const int new_timestamp, const InputFrame& map_frame){
    latest_timestamp = new_timestamp;
    map_frames->push_back(map_frame);
}
