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
    int speed;
    int probabilistic_movement;
    int id;


protected:
    // для изменения координаты z,
    // предпологается что в классе SimulationObject нет метода получения координаты z
    Coordinates *pos = nullptr;
    std::vector<Coordinates*> list_point;

    bool found_move;

public:
    SimulationObject(\
        int id, int pos_x, int pos_y, int size_x, int size_y, \
        int speed, int probabilistic_movement);

    ~SimulationObject();
    virtual bool random_walk(int map_size_x, int map_size_y);

    int get_size_x();
    int get_size_y();
    int get_pos_x();
    int get_pos_y();
    int get_probabilistic_movement();
    //int set_probabilistic_movement();
    int get_speed();
    //int set_speed();
    int get_id();
    int get_count_point();
    bool get_found_move();
    void set_found_move(bool move);
    virtual std::string get_info_parametrs();
    int return_distance_to_obj(SimulationObject *obj);
    int return_distance_current();


};


//--------------------

int create_random_id(std::vector<SimulationObject*> *list_obj);
SimulationObject *create_random_SimulationObject(\
        std::vector<SimulationObject*> *list_obj, int map_size_x, int map_size_y);

#endif // SIMULATIONOBJECT_HPP
