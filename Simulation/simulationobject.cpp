#include "simulationobject.hpp"
#include "base_functions.hpp"

#include <iostream>
#include <vector>
#include <cmath>


#include <stdlib.h>

//---------------------------------
SimulationObject::SimulationObject(\
        int id, int pos_x, int pos_y, int size_x, int size_y, \
        int speed, int probabilistic_movement) : id(id),\
    size_x(size_x), size_y(size_y), speed(speed), probabilistic_movement(probabilistic_movement)
{
    pos = new Coordinates(pos_x, pos_y);
    list_point.push_back(pos);
    found_move = false;
    std::cout<<"Create object: "<<id<<std::endl;
}
SimulationObject::~SimulationObject(){
    //pos - находится в списке точек
    int i;
    for(i = 0; i < list_point.size(); ++i){
        delete list_point[i];
        list_point[i] = nullptr;
    }
    list_point.clear();
}
// Случайное движение, если позиция изменина возврат true
bool SimulationObject::random_walk(int map_size_x, int map_size_y){
    int direction = rand() % probabilistic_movement;
    int x_move = 0, y_move = 0;
    if(direction == 0){
        if(pos->get_x() + speed <= map_size_x - size_x){
            x_move = speed;
        }
    }
    else if(direction == 1){
        if(pos->get_x() - speed >= 0){
            x_move = -1 * speed;
        }
    }
    else if(direction == 2){
        if(pos->get_y() + speed <= map_size_y - size_y){
            y_move = speed;
        }
    }
    else if(direction == 3){
        if(pos->get_y() - speed >= 0){
            y_move = -1 * speed;
        }
    }
    if(x_move != 0 || y_move != 0){
        Coordinates *new_pos = new Coordinates(pos->get_x() + x_move, pos->get_y() + y_move);
        pos = new_pos;
        list_point.push_back(pos);
        found_move = true;

        //list_points->addPoints(pos_x, pos_y);
        return true;
    }
    found_move = false;
    return false;
}

int SimulationObject::return_distance_to_obj(SimulationObject *obj){
    int dist = distance_points(pos->get_x(), pos->get_y(), obj->get_pos_x(), obj->get_pos_y());
    return dist;
}
int SimulationObject::return_distance_current(){
    int dist = 0;
    int i = 0, i2;
    for(i2 = 1; i2 < list_point.size(); ++i2, ++i){
        dist += distance_points(list_point[i]->get_x(), list_point[i]->get_y(),\
                                list_point[i2]->get_x(), list_point[i2]->get_y());

    }
    return dist;
}

int SimulationObject::get_id(){
    return id;
}
int SimulationObject::get_pos_x(){
    return pos->get_x();

}
int SimulationObject::get_pos_y(){
    return pos->get_y();
}
int SimulationObject::get_size_x(){
    return size_x;
}
int SimulationObject::get_size_y(){
    return size_y;
}
int SimulationObject::get_speed(){
    return speed;
}
int SimulationObject::get_count_point(){
    return list_point.size();
}
bool SimulationObject::get_found_move(){
    return found_move;
}

std::string SimulationObject::get_info_parametrs(){
    std::string info = "id: " + std::to_string(id);
    info += "  size: " + std::to_string(size_x) + ", "+ std::to_string(size_y);
    info += "  pos_on_map: " + std::to_string(pos->get_x()) + ", " + std::to_string(pos->get_y());
    info += "\ncount point: " + std::to_string(get_count_point());
    info += "\nspeed: " + std::to_string(speed) + " distance: " + std::to_string(return_distance_current());
    return info;
}


//-------------------------------------------
UserEquipment::UserEquipment(\
    int id, int pos_x, int pos_y, int pos_z, \
    int size_x, int size_y, int size_z, int speed, int probabilistic_movement, double scale_lon) : \
    SimulationObject(id, pos_x, pos_y, size_x, size_y, speed, probabilistic_movement)
{
    pos->set_z(pos_z);
    this->size_z = size_z;
    this->scale_lon = scale_lon;
    std::cout<<"[TEST]\n";
}

int UserEquipment::get_pos_z(){
    return pos->get_z();
}
double UserEquipment::get_lon(){
    double x = (double)get_pos_x();
    double y = (double)get_pos_y();
    return atan2((double)x, (double)y);
}
double UserEquipment::get_lat(){

    return 0;//Временная заглушка
}


double UserEquipment::return_distance_to_obj(UserEquipment *obj){
    return distance_points_lat_lon(get_lat(), get_lon(), obj->get_lat(), obj->get_lon());
}

std::string UserEquipment::get_info_parametrs(){
    std::string info = "id: " + std::to_string(get_id());
    info += "  size: " + std::to_string(get_size_x()) + ", "+ std::to_string(get_size_y());
    info += "  pos_on_map: " + std::to_string(pos->get_x()) + ", " + std::to_string(pos->get_y());
    info += "\ncount point: " + std::to_string(get_count_point());
    info += "\nspeed: " + std::to_string(get_speed()) + " distance: " + std::to_string(return_distance_current());
    info +="  lan: "+ std::to_string(get_lat()) +"lat" + std::to_string(get_lon());
    return info;
}

//--------------------------------------
Coordinates::Coordinates(int x, int y) : x(x), y(y)
{
    z = 0;

}
Coordinates::Coordinates(int x, int y, int z) : x(x), y(y), z(z)
{

}
// Не доделана
Coordinates::Coordinates(double lat, double lon){
    this->lat = lat;
    this->lon = lon;
    //x = R * cos(lat)
}
Coordinates::~Coordinates(){
    //delete this;
}
int Coordinates::get_x(){
    return x;
}
int Coordinates::get_y(){
    return y;
}
int Coordinates::get_z(){
    return z;
}
void Coordinates::set_x(int x){
    this->x = x;
}
void Coordinates::set_y(int y){
    this->y = y;
}
void Coordinates::set_z(int z){
    this->z = z;
}
double Coordinates::get_lat(){
    return asin((double)z / R);
}
double Coordinates::get_lon(){
    return atan2((double)x, (double)y);
}
// не доработана
void Coordinates::set_lat(double lat){
    this->lat = lat;
}
void Coordinates::set_lon(double lon){
    this->lon = lon;
}



//-----------------------------------------

Point_xy::Point_xy(int x, int y){
    this->x = x;
    this->y = y;
}
Point_xy::~Point_xy(){

}
int Point_xy::get_x(){
    return x;
}
int Point_xy::get_y(){
    return y;
}
void Point_xy::set_x(int x){
    this->x = x;
}
void Point_xy::set_y(int y){
    this->y = y;
}

//---------------------------
Point_xyz::Point_xyz(double x, double y, double z) : x(x), y(y), z(z){}

Point_xyz::~Point_xyz(){}
double Point_xyz::get_x(){
    return x;
}
double Point_xyz::get_y(){
    return y;
}
double Point_xyz::get_z(){
    return z;
}
void Point_xyz::set_x(double x){
    this->x = x;
}
void Point_xyz::set_y(double y){
    this->y = y;
}
void Point_xyz::set_z(double z){
    this->z = z;
}



//---------------------------------------------
// Объект со случайными параметрами
SimulationObject *create_random_SimulationObject(\
        std::vector<SimulationObject*> *list_obj, int map_size_x, int map_size_y )
{
    int id = create_random_id(list_obj);
    int size_x = (rand() % 50) + 20;
    int size_y = size_x;
    int pos_x = (rand() % (map_size_x - size_x));
    int pos_y = (rand() % (map_size_y - size_y));
    int speed = (rand() % 50) + 1;
    int prob_mov = (rand() % 20) + 4;

    SimulationObject *new_obj = new SimulationObject(\
                id, pos_x, pos_y, size_x, size_y, speed, prob_mov);
    return new_obj;
}

UserEquipment *create_random_UserEquipment(\
        std::vector<SimulationObject*> *list_obj, int map_size_x, int map_size_y )
{
    int id = create_random_id(list_obj);
    int size_x = (rand() % 50) + 20;
    int size_y = size_x;
    int pos_x = (rand() % (map_size_x - size_x));
    int pos_y = (rand() % (map_size_y - size_y));
    int speed = (rand() % 50) + 1;
    int prob_mov = (rand() % 20) + 4;
    UserEquipment *new_obj = new UserEquipment(\
        id, pos_x, pos_y, 0, size_x, size_y, 1, speed, prob_mov);//0.03
    //SimulationObject *new_obj = new SimulationObject(\
    //            id, pos_x, pos_y, size_x, size_y, speed, prob_mov);
    return new_obj;
}
// Случайный id, не встречающийся в списке
int create_random_id(std::vector<SimulationObject*> *list_obj){
    int i;
    int new_id;
    bool found_id;
    while(true){
        new_id = (rand() % 10000) + 100;
        found_id = true;
        for(i = 0; i < list_obj->size(); ++i){
            if((*list_obj)[i]->get_id() == new_id){
                found_id = false;
                break;
            }
        }
        if(found_id){
            return new_id;
        }

    }

}
// на удаление
int create_random_id1(std::vector<UserEquipment*> *list_obj){
    int i;
    int new_id;
    bool found_id;
    while(true){
        new_id = (rand() % 10000) + 100;
        found_id = true;
        for(i = 0; i < list_obj->size(); ++i){
            if((*list_obj)[i]->get_id() == new_id){
                found_id = false;
                break;
            }
        }
        if(found_id){
            return new_id;
        }

    }

}


















