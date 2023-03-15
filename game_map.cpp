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

InputFrame GameMap::getFrameBySerial(const int serial) {
    return getFrameBySerial(serial, serial);
}

InputFrame GameMap::getFrameBySerial(const int serial, const int search_start_frame) {
    InputFrame frame = map_frames->at(search_start_frame);
    if(frame.timestamp == serial){
        return frame;
    } else {
        for (int i = 0; i < 3; ++i) {
            frame = map_frames->at(search_start_frame - i);
            if(frame.timestamp == serial) {
                return frame;
            }
            frame = map_frames->at(search_start_frame + i);
            if(frame.timestamp == serial) {
                return frame;
            }
        }
        std::cout << "game over";
        return map_frames->at(0);
    }
}
