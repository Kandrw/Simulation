#ifndef SIMULATIONMAP_HPP
#define SIMULATIONMAP_HPP

#include "simulationobject.hpp"

#include <vector>

class Coordinates;

class SimulationMap
{
public:
    SimulationMap(int sizeX, int sizeY, int posX, int posY);
    ~SimulationMap();

    int get_count_obj();

    void objects_random_walk();
    int get_posX();
    int get_posY();
    int get_sizeX();
    int get_sizeY();
    //int get_count
    void set_posX(int x);
    void set_posY(int y);

    SimulationObject* get_obj_by_index(int index);
    SimulationObject* get_obj_by_id(int id);

    SimulationObject* create_new_object();
    void delete_obj_all();
    int delete_obj_by_id(int id);

private:
    int map_size_x, map_size_y;
    //int map_pos_x, map_pos_y;
    Coordinates *pos;
    //int count_obj;
    //int map_scale = 0;
    std::vector <SimulationObject*> list_object;
};



#endif // SIMULATIONMAP_HPP
