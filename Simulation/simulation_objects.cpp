#include "simulation_objects.hpp"

#include <iostream>
#include <stdlib.h>
#include <string>

#include <QtWidgets>

Stack_points_xy::Stack_points_xy(int x, int y) : x(x), y(x){

}


ListPoints::ListPoints(int x, int y){
    head_stack = new Stack_points_xy(x, y);
    end_stack = head_stack;
    count_points = 1;
}

void ListPoints::addPoints(int x1, int y1){
    count_points++;
    end_stack->next = new Stack_points_xy(x1, y1);
    end_stack = end_stack->next;
}




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
        new_id = rand() % MAX_ID + 10;
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

Object_label *search_id_object_list(Stack_object *list, int id){
    Stack_object *i_ptr = list->next;
    while(i_ptr){
        if(i_ptr->id == id){
            return i_ptr->ptr_object;
        }
        i_ptr = i_ptr->next;
    }
    return nullptr;
}

bool delete_object_list_by_id(Stack_object *list, int id){
    Stack_object *i_ptr = list->next, *i_ptr_prev = list;
    while(i_ptr){
        if(i_ptr->id == id){
            i_ptr_prev->next = i_ptr->next;
            delete i_ptr->ptr_object;
            delete i_ptr;
            list->id--;
            return true;
        }
        i_ptr_prev = i_ptr;
        i_ptr = i_ptr->next;
    }
    return false;
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
    list_points = new ListPoints(pos_x, pos_y);

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


    if(x_move != 0 || y_move != 0){
        pos_x += x_move;
        pos_y += y_move;
        list_points->addPoints(pos_x, pos_y);
        form_visual->setGeometry(pos_x, pos_y, size_x, size_y);
    }


}

std::string Object_label::return_info_params(){
    std::string parameters = "x = ";
    parameters += std::to_string(pos_x);
    parameters += " y = " + std::to_string(pos_y);
    parameters += ", size("+std::to_string(size_x)+" "+std::to_string(size_y)+")";
    parameters += "\n ID = " + std::to_string(id) + " speed = "+std::to_string(speed);
    parameters += " count points = "+std::to_string(list_points->count_points);
    return parameters;
}

bool Object_label::return_cursor_touch(int x_cursor, int y_cursor){
    if((x_cursor >= pos_x && x_cursor <= pos_x+size_x) && \
    (y_cursor >= pos_y && y_cursor <= pos_y+size_y))
    {
        std::cout<<"\tid = "<<id<<std::endl;
        return true;
    }
    return false;


}











