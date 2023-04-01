#ifndef GEOSIMULATIONMAP_HPP
#define GEOSIMULATIONMAP_HPP

#include "simulationobject.hpp"
#include "simulationmap.hpp"

#include <vector>

class Coordinates;



class GeoSimulationMap : public SimulationMap{
public:
    GeoSimulationMap(int sizeX, int sizeY, int sizeZ, double lat, double lon, double scale_lon);
    int get_sizeZ();
    double get_lat();
    double get_lon();

    //UserEquipment* create_new_object();
    SimulationObject* create_new_object();
    //void objects_random_walk();

private:
    int map_size_z;

    double lat, lon;
    //double lon_1_1000 = 0.03;
    double scale_lon;


};


#endif // GEOSIMULATIONMAP_HPP
