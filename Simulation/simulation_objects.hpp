#ifndef SIMULATION_OBJECTS_HPP
#define SIMULATION_OBJECTS_HPP
#define MAX_ID 111222

#include <iostream>

class QLabel;

class Object_label;


struct Stack_object{
    int id;
    Object_label *ptr_object = nullptr;
    Stack_object *next = nullptr;
    Stack_object(Object_label *ptr_object);
};

struct Stack_points_xy{
    int x, y;
    Stack_points_xy *next = nullptr;
    Stack_points_xy(int x, int y);

};
class ListPoints{
public:
    int count_points;
    Stack_points_xy *head_stack, *end_stack;
    ListPoints(int x, int y);
    void addPoints(int x1, int y1);
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

public:
    int size_x, size_y;
    int pos_x, pos_y;
    int probabilistic_movement;
    int speed;
    const int id;
public:

    QLabel *form_visual;
    ListPoints *list_points;

};



void insert_list_object(Stack_object *list, Object_label *ptr_object);
int Create_id_object(Stack_object *list);
Object_label *search_id_object_list(Stack_object *list, int id);
bool delete_object_list_by_id(Stack_object *list, int id);
int add_percentage(int number, int percent);


#endif // SIMULATION_OBJECTS_HPP
