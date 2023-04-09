#include "GeoSimulationMap.hpp"
#include "simulationmap.hpp"
#include "base_functions.hpp"
#include "Coordinates.hpp"
#include "simulationobject.hpp"
#include "UserEquipment.hpp"

#include "output.hpp"

//Altitude не доделано
GeoSimulationMap::GeoSimulationMap(int sizeX, int sizeY, int sizeZ,\
    double lat1, double lon1, double lat2, double lon2, int posX = 10, int posY = 100) : \
    SimulationMap(sizeX, sizeY, posX, posY), map_size_z(sizeZ)
{
    Output::cout("Create GeoSM\n");
    point_1 = new Coordinates(lat1, lon1, 0.0);
    point_2 = new Coordinates(lat2, lon2, 0.0);
    scale = (lon2 - lon1)/(double)sizeX;
    Output::cout("scale = " + std::to_string(scale ) + "\n");


}
double GeoSimulationMap::get_lat(){
    return point_1->get_lat();
}
double GeoSimulationMap::get_lon(){
    return point_2->get_lon();
}

int GeoSimulationMap::get_sizeZ(){
    return map_size_z;
}
double GeoSimulationMap::get_scale(){
    return scale;
}
Coordinates *GeoSimulationMap::get_pos(){
    return point_1;
}

SimulationObject* GeoSimulationMap::create_new_object(){
    UserEquipment *new_obj = create_random_UserEquipment(&list_object, get_sizeX(), get_sizeY(), scale, point_1);

    list_object.push_back(new_obj);
    //std::cout<<"\tCreating obj - "<<new_obj->get_id()<<std::endl;
    Output::cout("\tCreating obj - " + std::to_string(new_obj->get_id()) + "\n");
    return new_obj;
}
void GeoSimulationMap::objects_random_walk(){
    int i;
    for(i = 0; i < list_object.size(); ++i){
        list_object[i]->random_walk(point_1, point_2);
    }
}

