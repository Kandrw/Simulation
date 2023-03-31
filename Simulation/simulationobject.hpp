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
    bool found_move;

protected:
    Coordinates *pos = nullptr;
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
    virtual std::string get_info_parametrs();
    int return_distance_to_obj(SimulationObject *obj);
    int return_distance_current();


};

class UserEquipment : public SimulationObject{
private:
    int size_z;
    double lat, lon;
    double scale_lon;

public:
    UserEquipment(\
        int id, int pos_x, int pos_y, int pos_z, int size_x, int size_y, int size_z, \
        int speed, int probabilistic_movement, double scale_lon = 0.03);// : SimulationObject(id, pos_x, pos_y, size_x, size_y, speed, probabilistic_movement);
    int get_pos_z();
    double get_lon();
    double get_lat();

    bool random_walk_lat_lon(int map_size_x, int map_size_y);
    double return_distance_to_obj(UserEquipment *obj);
    std::string get_info_parametrs() override;
};








//------------------

class Coordinates{
public:
    Coordinates(int x, int y);
    Coordinates(int x, int y, int z);
    Coordinates(double lat, double lon);

    ~Coordinates();
    int get_x();
    int get_y();
    int get_z();

    void set_x(int x);
    void set_y(int y);
    void set_z(int z);
    // Доделать
    double get_lat();
    double get_lon();

    void set_lat(double lat);
    void set_lon(double lon);



private:
    int x, y, z;
    double lat, lon;
    double R = 6371.0;

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
// Не используется
class Point_xyz{
private:
    double x, y, z;
public:
    Point_xyz(double x, double y, double z);
    ~Point_xyz();
    double get_x();
    double get_y();
    double get_z();
    void set_x(double x);
    void set_y(double y);
    void set_z(double z);
};


//--------------------

int create_random_id(std::vector<SimulationObject*> *list_obj);
SimulationObject *create_random_SimulationObject(\
        std::vector<SimulationObject*> *list_obj, int map_size_x, int map_size_y);
UserEquipment *create_random_UserEquipment(\
        std::vector<SimulationObject*> *list_obj, int map_size_x, int map_size_y );

#endif // SIMULATIONOBJECT_HPP
