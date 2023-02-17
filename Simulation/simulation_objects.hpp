#ifndef SIMULATION_OBJECTS_HPP
#define SIMULATION_OBJECTS_HPP
#define MAX_ID 111222

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
    Stack_points_xy *next;

};


class Object_label{
public:
    Object_label(int pos_x, int pos_y, int size_x, int size_y, \
                 int id, int speed, int probabilistic_movement);
    ~Object_label();
    void random_walk(int x_left, int x_right, int y_left, int y_right);

public:
    int size_x, size_y;
    int pos_x, pos_y;
    int probabilistic_movement;
    int speed;
    const int id;
public:

    QLabel *form_visual;


};



void insert_list_object(Stack_object *list, Object_label *ptr_object);
int Create_id_object(Stack_object *list);





#endif // SIMULATION_OBJECTS_HPP