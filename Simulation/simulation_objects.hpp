#ifndef SIMULATION_OBJECTS_HPP
#define SIMULATION_OBJECTS_HPP
#define MAX_ID 111222

#include <iostream>

class QLabel;

class Object_label;


struct Stack_object{
private:
    int id;
    Object_label *ptr_object = nullptr;
public:
    int get_id();
    void set_id(int new_id);
    //void add_id();
    Object_label *get_object();

    Stack_object *next = nullptr;

    Stack_object(Object_label *ptr_object);
    //~Stack_object
};

struct Stack_points_xy{
private:
    int x, y;
    Stack_points_xy *next = nullptr;
public:
    int get_x();
    int get_y();
    Stack_points_xy *get_next();
    void set_next(Stack_points_xy* new_next);


    Stack_points_xy(int x, int y);

};
class ListPoints{
private:
    int count_points;
public:

    Stack_points_xy *head_stack, *end_stack;
    ListPoints(int x, int y);
    void addPoints(int x1, int y1);
    int get_count_points();
    int set_count_points();

};

class Object_label{
public:
    Object_label(int pos_x, int pos_y, int size_x, int size_y, \
                 int id, int speed, int probabilistic_movement);
    ~Object_label();
    void random_walk(int map_size_x, int map_size_y);

    std::string return_info_params();

    bool return_cursor_touch(int x_cursor, int y_cursor);
    void draw(int x_new, int y_new, int scale);
    int return_distance_to_object(Object_label *ptr_object);
    int return_distance_to_point(int x, int y);
    int return_distance_current();

private:
    int size_x, size_y;
    int pos_x, pos_y;
    int probabilistic_movement;
    int speed;
    const int id;

public:

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




public:

    QLabel *form_visual;
    ListPoints *list_points;

};



void insert_list_object(Stack_object *list, Object_label *ptr_object);
int Create_id_object(Stack_object *list);
Object_label *search_id_object_list(Stack_object *list, int id);
bool delete_object_list_by_id(Stack_object *list, int id);



#endif // SIMULATION_OBJECTS_HPP
