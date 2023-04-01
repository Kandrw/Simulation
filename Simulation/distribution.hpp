#ifndef DISTRIBUTION_HPP
#define DISTRIBUTION_HPP

#include <vector>
#include <iostream>

class SimulationMap;
class MainWindow;
class SimulationObject;
class GeoSimulationMap;

//class UserEquipment;

//QT
class QLabel;

class Distribution
{
public:
    Distribution(MainWindow *mainwindow);
    ~Distribution();
    void create_new_object(int count);
    void render_scale_labels();
    void set_map_scale(int y);
    void set_map_scale_wheel_y(int y);
    void set_map_pos(int x, int y);
    void draw_labels();
    void draw_labels_objs_if_found_move();
    void draw_label_by_index(int index);
    void objs_random_walk();

    void set_old_mouse_pos(int x, int y);
    void move_simulation_by_mouse_pos(int x, int y);
    void delete_list_objects();
    int get_count_objs();
    void delete_obj_by_id(int id);
    void delete_select_obj_by_id();
    //void delete_list_label();
    //void delete_all_lists();

    SimulationObject* selecting_an_object_by_cursor(int x, int y);
    SimulationObject* return_select_object();
    //UserEquipment* selecting_an_object_by_cursor(int x, int y);


private:

    void add_obj_list_label(SimulationObject *obj);


    int map_scale_sim = 0;
    int size_factor = 10;
    SimulationMap *map = nullptr;
    //GeoSimulationMap *map = nullptr;

    QLabel *map_label = nullptr;
    MainWindow *mainwindow;
    std::vector <QLabel*> list_label_obj;
private:
    int old_mouse_pos_x, old_mouse_pos_y;
    // id выбранного объекта (0 - не выбран)
    int selected_object_id = 0;



};

#endif // DISTRIBUTION_HPP
