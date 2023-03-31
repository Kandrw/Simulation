#include "simulationmap.hpp"
#include "base_functions.hpp"

#include <iostream>


SimulationMap::SimulationMap(int sizeX, int sizeY, int posX, int posY)
{
    //map_pos_x = posX;
    //map_pos_y = posY;
    map_size_x = sizeX;
    map_size_y = sizeY;
    pos = new Coordinates(posX, posY);
    //count_obj = 0;
    std::cout<<"Create map"<<std::endl;
}
SimulationMap::~SimulationMap(){
    std::cout<<"Delete SimMap..."<<std::endl;
    int i;
    for(i = 0; i < list_object.size(); ++i){
        delete list_object[i];
        list_object[i] = nullptr;
    }
    list_object.clear();
    delete pos;
    std::cout<<"Delete SimMap"<<std::endl;
}

SimulationObject* SimulationMap::create_new_object(){
    std::cout<<"\tCreating obj..."<<std::endl;
    SimulationObject *new_obj = create_random_SimulationObject(&list_object, map_size_x, map_size_y);
    list_object.push_back(new_obj);
    std::cout<<"\tCreating obj - "<<new_obj->get_id()<<std::endl;
    return new_obj;
}

SimulationObject* SimulationMap::get_obj_by_index(int index){
    if(index < 0 || index >= list_object.size()){
        std::cout<<"[SimulationMap] Error: out of range"<<std::endl;
        return nullptr;
    }
    return list_object[index];
}
SimulationObject* SimulationMap::get_obj_by_id(int id){
    int i;
    for(i = 0; i < list_object.size(); ++i){
        if(list_object[i]->get_id() == id){
            return list_object[i];
        }
    }
    return nullptr;
}

void SimulationMap::objects_random_walk(){
    int i;
    for(i = 0; i < list_object.size(); ++i){
        list_object[i]->random_walk(map_size_x, map_size_y);
    }
}
// Удалить все объекты
void SimulationMap::delete_obj_all(){
    int i;
    for(i = 0; i < list_object.size(); ++i){
        delete list_object[i];
        list_object[i] = nullptr;
    }
    list_object.clear();
}
// удаление по id, результат позиция в списке
int SimulationMap::delete_obj_by_id(int id){
    int i;
    for(i = 0; i < list_object.size(); ++i){
        if(list_object[i]->get_id() == id){
            list_object.erase(list_object.cbegin() + i);

            return i;
        }
    }
    return -1;
}


int SimulationMap::get_count_obj(){
    return list_object.size();
}
int SimulationMap::get_posX(){
    return pos->get_x();
}
int SimulationMap::get_posY(){
    return pos->get_y();
}
int SimulationMap::get_sizeX(){
    return map_size_x;
}
int SimulationMap::get_sizeY(){
    return map_size_y;
}
void SimulationMap::set_posX(int x){
    pos->set_x(x);
}
void SimulationMap::set_posY(int y){
    pos->set_y(y);
}
//---------------------------------------------------

GeoSimulationMap::GeoSimulationMap(int sizeX, int sizeY, int sizeZ, double lat, double lon) : \
    SimulationMap(sizeX, sizeY, 10, 100), lat(lat), lon(lon), map_size_z(sizeZ) {
    std::cout<<"lon pos = "<<lon<<std::endl;
}
//Не проверено
double GeoSimulationMap::get_lat(){
    return lat;
}
double GeoSimulationMap::get_lon(){
    return lon;
}
int GeoSimulationMap::get_sizeZ(){
    return map_size_z;
}
/*
UserEquipment* GeoSimulationMap::create_new_object(){
    std::cout<<"\tCreating obj..."<<std::endl;
    //SimulationObject *new_obj = create_random_SimulationObject(&list_object, map_size_x, map_size_y);
    //SimulationObject *new_obj = create_random_SimulationObject(&list_object, get_sizeX(), get_sizeY());

    UserEquipment *new_obj = create_random_UserEquipment(&list_object, get_sizeX(), get_sizeY());
    list_object.push_back(new_obj);
    std::cout<<"\tCreating obj - "<<new_obj->get_id()<<std::endl;
    return new_obj;
}

*/
SimulationObject* GeoSimulationMap::create_new_object(){
    std::cout<<"\tCreating obj..."<<std::endl;
    //SimulationObject *new_obj = create_random_SimulationObject(&list_object, map_size_x, map_size_y);
    //SimulationObject *new_obj = create_random_SimulationObject(&list_object, get_sizeX(), get_sizeY());

    UserEquipment *new_obj = create_random_UserEquipment(&list_object, get_sizeX(), get_sizeY());
    list_object.push_back(new_obj);
    std::cout<<"\tCreating obj - "<<new_obj->get_id()<<std::endl;
    return new_obj;
}
































