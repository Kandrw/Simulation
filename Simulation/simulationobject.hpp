#ifndef SIMULATIONOBJECT_HPP
#define SIMULATIONOBJECT_HPP


#include <vector>
#include <iostream>


class Coordinates;


//-------------------

class SimulationObject{
private:
    int size_x, size_y;

    //int pos_x, pos_y;
    Coordinates *pos = nullptr;
    int speed;
    int probabilistic_movement;
    int id;
    bool found_move;
    std::vector<Coordinates*> list_point;

public:
    SimulationObject(\
        int id, int pos_x, int pos_y, int size_x, int size_y, \
        int speed, int probabilistic_movement);

    ~SimulationObject();
    bool random_walk(int map_size_x, int map_size_y);

    int get_size_x();
    //int set_size_x();
    int get_size_y();
    //int set_size_y();
    int get_pos_x();
    //int set_pos_x();
    int get_pos_y();
    //int set_pos_y();
    //int get_probabilistic_movement();
    //int set_probabilistic_movement();
    int get_speed();
    //int set_speed();
    int get_id();
    int get_count_point();
    bool get_found_move();
    std::string get_info_parametrs();
    int return_distance_to_obj(SimulationObject *obj);
    int return_distance_current();

};

//------------------

class Coordinates{
public:
    Coordinates(int x, int y);
    ~Coordinates();
    int get_x();
    int get_y();
    void set_x(int x);
    void set_y(int y);
private:
    int x, y;

};
//---------------------

class Point_xy{
private:
    int x, y;
public:
    Point_xy(int x, int y);
    ~Point_xy();
    int get_x();
    int get_y();
    void set_x(int x);
    void set_y(int y);
};

//--------------------

int create_random_id(std::vector<SimulationObject*> *list_obj);
SimulationObject *create_random_SimulationObject(\
        std::vector<SimulationObject*> *list_obj, int map_size_x, int map_size_y);


#endif // SIMULATIONOBJECT_HPP
