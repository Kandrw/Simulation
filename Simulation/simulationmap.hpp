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

    virtual void objects_random_walk();

    int get_posX();
    int get_posY();
    int get_sizeX();
    int get_sizeY();

    void set_posX(int x);
    void set_posY(int y);

    SimulationObject* get_obj_by_index(int index);
    SimulationObject* get_obj_by_id(int id);

    virtual SimulationObject* create_new_object();
    void delete_obj_all();
    int delete_obj_by_id(int id);

    virtual double get_scale();
    virtual Coordinates *get_pos();

protected:
    Coordinates *pos;
    std::vector <SimulationObject*> list_object;
private:
    int map_size_x, map_size_y;

};






#endif // SIMULATIONMAP_HPP
