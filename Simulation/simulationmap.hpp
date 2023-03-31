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
    //int get_map_size_x();
    //int get_map_size_y();

    //int get_count
    void set_posX(int x);
    void set_posY(int y);

    SimulationObject* get_obj_by_index(int index);
    SimulationObject* get_obj_by_id(int id);

    virtual SimulationObject* create_new_object();
    void delete_obj_all();
    int delete_obj_by_id(int id);
protected:
    Coordinates *pos;
    std::vector <SimulationObject*> list_object;
private:
    int map_size_x, map_size_y;
    //int map_pos_x, map_pos_y;

    //int count_obj;
    //int map_scale = 0;

};

class GeoSimulationMap : public SimulationMap{
public:
    GeoSimulationMap(int sizeX, int sizeY, int sizeZ, double lat, double lon);
    int get_sizeZ();
    double get_lat();
    double get_lon();

    //UserEquipment* create_new_object();
    SimulationObject* create_new_object();

private:
    int map_size_z;
    double lat = 0.0, lon = 83.1068;
    double lon_1_1000 = 0.03;


};





#endif // SIMULATIONMAP_HPP
