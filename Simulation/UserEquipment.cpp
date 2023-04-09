#include "base_functions.hpp"
#include "UserEquipment.hpp"
#include "simulationobject.hpp"
#include "Coordinates.hpp"

#include "output.hpp"

#include <iostream>
#include <vector>
#include <cmath>

#include <stdlib.h>


/*
UserEquipment::UserEquipment(\
    int id, int pos_x, int pos_y, int pos_z, \
    int size_x, int size_y, int size_z, int speed, int probabilistic_movement, double scale) : \
    SimulationObject(id, pos_x, pos_y, size_x, size_y, speed, probabilistic_movement)
{
    pos->set_z(pos_z);
    this->size_z = size_z;
    this->scale = scale;
    std::cout<<"[TEST]\n";
}
*/
UserEquipment::UserEquipment(\
    int id, double lat, double lon, double alt, \
    int size_x, int size_y, int size_z, int speed, int probabilistic_movement, double scale) : \
    SimulationObject(id, 400, 400, size_x, size_y, speed, probabilistic_movement)
{
    //pos->set_z(pos_z);
    pos->set_lat(lat);
    pos->set_lon(lon);
    pos->set_alt(alt);
    this->size_z = size_z;
    this->scale = scale;
}


int UserEquipment::get_pos_z(){
    return pos->get_z();
}
double UserEquipment::get_lon(){

    /*
    double x = (double)get_pos_x();
    double y = (double)get_pos_y();
    return atan2((double)x, (double)y);
    */
    return pos->get_lon();
}
double UserEquipment::get_lat(){

    return pos->get_lat();

}


double UserEquipment::return_distance_to_obj(UserEquipment *obj){
    return distance_points_lat_lon(get_lat(), get_lon(), obj->get_lat(), obj->get_lon());
}

std::string UserEquipment::get_info_parametrs(){
    std::string info = "id: " + std::to_string(get_id());
    info += "  size: " + std::to_string(get_size_x()) + ", "+ std::to_string(get_size_y());
    info += "  pos_on_map: " + std::to_string(pos->get_x()) + ", " + std::to_string(pos->get_y());
    info += "\ncount point: " + std::to_string(get_count_point());
    info += "  speed: " + std::to_string(get_speed()) + "  distance: " + std::to_string(return_distance_current());

    info += "\nlat: "+ std::to_string(get_lat()) +"  lon: " + std::to_string(get_lon());


    if(get_count_point() % 10 == 0){
        int i = get_count_point() - 10;
        if(i < 0){
            i = 0;
        }
        Output::cout("[Coords]\n");

        Coordinates *Cs;
        for(; i < get_count_point(); ++i){
            Cs = list_point[i];
            Output::cout("[ " + std::to_string( i ) + " ]\n");

            Output::cout( "lat = " + std::to_string(Cs->get_lat()) + "  lon = " + std::to_string(Cs->get_lon()) + "\n");
        }
    }
    return info;
}





UserEquipment *create_random_UserEquipment(\
        std::vector<SimulationObject*> *list_obj, int map_size_x, int map_size_y, double scale, Coordinates *point)
{
    int id = create_random_id(list_obj);
    int size_x = (rand() % 50) + 20;
    int size_y = size_x;

    int speed = (rand() % 50) + 1;
    int prob_mov = (rand() % 20) + 4;

    int pos_x = (rand() % (map_size_x - size_x));
    int pos_y = (rand() % (map_size_y - size_y));

    double lat = point->get_lat() + scale * (double)pos_y;
    double lon = point->get_lon() + scale * (double)pos_x;


    //UserEquipment *new_obj = new UserEquipment(\
      //  id, pos_x, pos_y, 0, size_x, size_y, 1, speed, prob_mov, scale);
    UserEquipment *new_obj = new UserEquipment(\
        id, lat, lon, 0.0, size_x, size_y, 1, speed, prob_mov, scale);
    //std::cout<<"[create] lat "<<lat<<"  lon = "<<lon<<"\n";

    return new_obj;
}

// Случайное движение, если позиция изменена возврат true

bool UserEquipment::random_walk(Coordinates *point1, Coordinates *point2){
    int direction = rand() % get_probabilistic_movement();
    //direction = 1;
    int x_move = 0, y_move = 0;
    // lat
    if(direction == 0){
        if(pos->get_lat() + ((double)get_speed() * scale) <= point2->get_lat() - ((double)get_size_x() * scale) ){
            y_move = get_speed();
        }
    }
    else if(direction == 1){
        if(pos->get_lat() - ((double)get_speed() * scale) >= point1->get_lat()){
            y_move = -1 * get_speed();
        }
    }
    //lon
    else if(direction == 2){
        if(pos->get_lon() + ( (double)get_speed() * scale ) <= point2->get_lon() - ((double)get_size_y() * scale) ){
            x_move = get_speed();
        }
    }
    else if(direction == 3){
        if(pos->get_lon() - ((double)get_speed() * scale) >= point1->get_lon()){
            x_move = -1 * get_speed();
        }
    }
    if(x_move != 0 || y_move != 0){
        //double lat
        //Coordinates *new_pos = new Coordinates(pos->get_x() + x_move, pos->get_y() + y_move);
        double lat = pos->get_lat() + ( (double)y_move * scale );
        double lon = pos->get_lon() + ( (double)x_move * scale );
        //std::cout<<"[move] lat "<<lat<<"  lon = "<<lon<<"\n";
        Coordinates *new_pos = new Coordinates(lat, lon, pos->get_alt());

        pos = new_pos;
        list_point.push_back(pos);
        set_found_move(true);
        return true;
    }
    set_found_move(false);
    return false;
}



