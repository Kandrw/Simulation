#ifndef USEREQUIPMENT_HPP
#define USEREQUIPMENT_HPP

#include "simulationobject.hpp"

#include <vector>
#include <iostream>


//class SimulationObject;


class UserEquipment : public SimulationObject{
private:
    int size_z;
    //double lat, lon;
    // Не используется
    double scale;

public:
    //UserEquipment(\
     //   int id, int pos_x, int pos_y, int pos_z, int size_x, int size_y, int size_z, \
    //    int speed, int probabilistic_movement, double scale);// : SimulationObject(id, pos_x, pos_y, size_x, size_y, speed, probabilistic_movement);
    UserEquipment(\
        int id, double lat, double lon, double alt, \
        int size_x, int size_y, int size_z, int speed, \
            int probabilistic_movement, double scale);
    int get_pos_z();
    double get_lon();
    double get_lat();

    //bool random_walk_lat_lon(int map_size_x, int map_size_y);
    //bool random_walk(int map_size_x, int map_size_y);
    bool random_walk(Coordinates *point1, Coordinates *point2);
    double return_distance_to_obj(UserEquipment *obj);
    std::string get_info_parametrs();
};
UserEquipment *create_random_UserEquipment(\
    std::vector<SimulationObject*> *list_obj, \
        int map_size_x, int map_size_y, double scale, Coordinates *point );






#endif // USEREQUIPMENT_HPP
