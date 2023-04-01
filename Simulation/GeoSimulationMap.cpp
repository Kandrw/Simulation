#include "GeoSimulationMap.hpp"
#include "simulationmap.hpp"
#include "base_functions.hpp"
#include "Coordinates.hpp"
#include "simulationobject.hpp"
#include "UserEquipment.hpp"



GeoSimulationMap::GeoSimulationMap(int sizeX, int sizeY, int sizeZ, double lat, double lon, double scale_lon) : \
    SimulationMap(sizeX, sizeY, 10, 100), lat(lat), lon(lon), map_size_z(sizeZ), scale_lon(scale_lon) {
    std::cout<<"lon pos = "<<lon<<std::endl;
    std::cout<<"scale lon = "<<scale_lon<<std::endl;

}

double GeoSimulationMap::get_lat(){
    return lat;
}
double GeoSimulationMap::get_lon(){
    return lon;
}

int GeoSimulationMap::get_sizeZ(){
    return map_size_z;
}


SimulationObject* GeoSimulationMap::create_new_object(){
    //std::cout<<"\tCreating obj..."<<std::endl;
    UserEquipment *new_obj = create_random_UserEquipment(&list_object, get_sizeX(), get_sizeY(), scale_lon);
    list_object.push_back(new_obj);
    //std::cout<<"\tCreating obj - "<<new_obj->get_id()<<std::endl;
    return new_obj;
}


