#include <iostream>
#include <vector>

/*
 * this class has been implemented with this assumption that you are using a 3rd party library to connect
 * to the actuator and buttons and sensors
 * */
enum STATE {
    UP=1, Down=2, STOP=3, DOORS_OPEN=4, DOORS_CLOSE=4
};

class Control{
public:
    Control(int floor_num){
        current_door = new STATE[floor_num];
    };
    ~Control(){
        delete[] current_door;
    };
    int door_button(int door_number=0){
        if(doors_.back() != door_number){
            doors_.push_back(door_number);
            return 0;
        }
        return 1;
    }
    int elevator_button(int floor=0){
        if(floors_.back() != floor){
            floors_.push_back(floor);
            return 0;
        }
        return 1;
    }
    int sensor_floor(int floor=0){
        if(floors_.front() == floor){
            floors_.erase(floors_.begin());
            if(doors_.front() == floor)doors_.erase(doors_.begin());
            return stop(floor);
        }
        if(doors_.front() == floor){
            doors_.erase(doors_.begin());
            return stop(floor);
        }
        return go_2_floor(floor);
    }
    int sensor_door_open(int floor=0){
        current_door[floor] == STATE::DOORS_OPEN;
    }
    int sensor_door_close(int floor=0){
        current_door[floor] == STATE::DOORS_CLOSE;
        return go_2_floor(floor);
    }
private:
    STATE current_elevator;
    STATE* current_door;
    std::vector<int> doors_;
    std::vector<int> floors_;
    int stop(int floor){
        current_elevator == STATE::STOP;
        if(envok_3d_patry_stop())open_door(floor);
    }
    int go_2_floor(int current_floor){
        if(doors_.size() > 0 && floors_.size() > 0) {
            int dis_d = current_floor - doors_.front(), dis_f = current_floor - floors_.front();
            if (current_elevator == STATE::UP) {
                if (dis_f > 0 || dis_d > 0) {
                    envok_3d_party_go_Up();
                }
                envok_3d_party_go_Down();
                current_elevator = STATE::Down;
            }
            if (current_elevator == STATE::Down) {
                if (dis_f < 0 || dis_d < 0) {
                    envok_3d_party_go_Down();
                }
                envok_3d_party_go_Up();
                current_elevator = STATE::UP;
            }
            if (current_elevator == STATE::STOP) {
            int min=std::min(abs(dis_f),abs(dis_d));
                if (min > 0) {
                    envok_3d_party_go_Up();
                    current_elevator = STATE::UP;
                }
                envok_3d_party_go_Down();
                current_elevator = STATE::Down;
            }
        }
    }
    int open_door(int floor){
        if(current_door[floor] == STATE::DOORS_CLOSE)envok_3d_patry_open_door();
    }
};
