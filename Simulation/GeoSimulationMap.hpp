#ifndef GEOSIMULATIONMAP_HPP
#define GEOSIMULATIONMAP_HPP

#include "simulationobject.hpp"
#include "simulationmap.hpp"

#include <vector>

class Coordinates;



class GeoSimulationMap : public SimulationMap{
public:
    //GeoSimulationMap(int sizeX, int sizeY, int sizeZ, \
    //    double lat, double lon, double scale_lon, int posX, int posY);
    GeoSimulationMap(int sizeX, int sizeY, int sizeZ,\
        double lat1, double lon1, double lat2, double lon2, int posX, int posY);
    int get_sizeZ();
    double get_lat();
    double get_lon();

    double get_scale();
    Coordinates *get_pos();
    //UserEquipment* create_new_object();
    SimulationObject* create_new_object();
    void objects_random_walk();


private:
    int map_size_z;

    double lat, lon;
    Coordinates *point_1;
    Coordinates *point_2;
    //double lon_1_1000 = 0.03;
    double scale;


};


#endif // GEOSIMULATIONMAP_HPP
