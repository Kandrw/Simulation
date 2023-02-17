#include "simulation_objects.hpp"

#include <iostream>
#include <stdlib.h>

#include <QtWidgets>


Stack_object::Stack_object(Object_label *ptr_object) : ptr_object(ptr_object)
{
    if(ptr_object){

        id = ptr_object->id;
    }
    else{
        id = 0;
    }
}

void insert_list_object(Stack_object *list, Object_label *ptr_object){
    Stack_object *ptr = list;
    while(ptr->next){
        ptr = ptr->next;
    }
    ptr->next = new Stack_object(ptr_object);

    list->id++;
}

int Create_id_object(Stack_object *list){

    int new_id, found_id = 0;
    Stack_object *i_stack_object;
    while(1){
        new_id = rand() % MAX_ID;
        i_stack_object = list->next;
        while(i_stack_object){
            if(i_stack_object->id == new_id){
                found_id = 1;
                break;
            }
            i_stack_object = i_stack_object->next;
        }
        if(!found_id){
            break;
        }
    }
    std::cout<<"[new id = "<<new_id<<"]\n";
    return new_id;

}

Object_label::Object_label(\
    int pos_x, int pos_y, int size_x, int size_y, \
    int id, int speed, int probabilistic_movement) : pos_x(pos_x), pos_y(pos_y), \
        size_x(size_x), size_y(size_y), id(id), speed(speed), \
        probabilistic_movement(probabilistic_movement)
{
    form_visual = new QLabel("");
    form_visual->setGeometry(pos_x, pos_y, size_x, size_y);
    form_visual->setStyleSheet("background-color : #DAA520");

}

Object_label::~Object_label(){
    delete form_visual;
}


void Object_label::random_walk(int x_left, int x_right, int y_up, int y_down){
    int direct = rand() % probabilistic_movement;
    int x_move = 0, y_move = 0;
    if(direct == 0){
        if(pos_x + speed + size_x<= x_right)
            x_move += speed;
    }
    else if(direct == 1){
        if(pos_x - speed >= x_left)
            x_move -= speed;
    }
    else if(direct == 2){
        if(pos_y + speed + size_y <= y_down)
            y_move += speed;
    }
    else if(direct == 3){
        if(pos_y - speed >= y_up)
            y_move -= speed;
    }

    pos_x += x_move;
    pos_y += y_move;
    form_visual->setGeometry(pos_x, pos_y, size_x, size_y);

}





