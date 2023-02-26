#include "simulation_objects.hpp"
#include "basi_functions.hpp"

#include <iostream>
#include <stdlib.h>
#include <string>

#include <QtWidgets>


//

Stack_points_xy::Stack_points_xy(int x, int y) : x(x), y(x){

}
int Stack_points_xy::get_x(){
    return x;
}
int Stack_points_xy::get_y(){
    return y;
}

Stack_points_xy* Stack_points_xy::get_next(){
    return next;
}
void Stack_points_xy::set_next(Stack_points_xy* new_next){
    next = new_next;
}

//

ListPoints::ListPoints(int x, int y){
    head_stack = new Stack_points_xy(x, y);
    end_stack = head_stack;
    count_points = 1;
}

void ListPoints::addPoints(int x1, int y1){
    count_points++;
    //end_stack->next =
    end_stack->set_next(new Stack_points_xy(x1, y1));
    end_stack = end_stack->get_next();
}
int ListPoints::set_count_points(){

}
int ListPoints::get_count_points(){
    return count_points;
}


//

Stack_object::Stack_object(Object_label *ptr_object) : ptr_object(ptr_object)
{
    if(ptr_object){

        id = ptr_object->get_id();
    }
    else{
        id = 0;
    }
}

int Stack_object::get_id(){
    return id;
}
void Stack_object::set_id(int new_id){
    if(!ptr_object){
        id = new_id;
    }
    else{
        std::cout<<"Error: you can change the id if the object does not exist"<<std::endl;
    }
}
Object_label* Stack_object::get_object(){
    return ptr_object;
}

Stack_object *Stack_object::get_next(){

    return next;
}
void Stack_object::set_next(Stack_object *new_next){
    next = new_next;
}


//

// вставка объекта в список
void insert_list_object(Stack_object *list, Object_label *ptr_object){
    Stack_object *ptr = list;
    while(ptr->get_next()){
        //ptr = ptr->next;
        ptr = ptr->get_next();
    }
    //ptr->next = new Stack_object(ptr_object);
    ptr->set_next(new Stack_object(ptr_object));

    //list->id++;
    list->set_id(list->get_id() + 1);
}

int Create_id_object(Stack_object *list){

    int new_id, found_id = 0;
    Stack_object *i_stack_object;
    while(1){
        new_id = rand() % MAX_ID + 10;
        //i_stack_object = list->next;
        i_stack_object = list->get_next();

        while(i_stack_object){
            if(i_stack_object->get_id() == new_id){
                found_id = 1;
                break;
            }
            //i_stack_object = i_stack_object->next;
            i_stack_object = i_stack_object->get_next();

        }
        if(!found_id){
            break;
        }
    }
    std::cout<<"[new id = "<<new_id<<"]\n";
    return new_id;

}
//найти объект по id в списке и вернуть на него указатель
Object_label *search_id_object_list(Stack_object *list, int id){
    //Stack_object *i_ptr = list->next;
    Stack_object *i_ptr = list->get_next();

    while(i_ptr){
        if(i_ptr->get_id() == id){
            //return i_ptr->ptr_object;
            return i_ptr->get_object();

        }
        //i_ptr = i_ptr->next;
        i_ptr = i_ptr->get_next();

    }
    return nullptr;
}
//найти объект по id в списке и удалить его
bool delete_object_list_by_id(Stack_object *list, int id){
    Stack_object *i_ptr = list->get_next(), *i_ptr_prev = list;
    while(i_ptr){
        if(i_ptr->get_id() == id){
            //i_ptr_prev->next = i_ptr->next;
            i_ptr_prev->set_next(i_ptr->get_next());

            //delete i_ptr->ptr_object;
            delete i_ptr->get_object();
            delete i_ptr;
            //list->id--;
            list->set_id(list->get_id() - 1);
            return true;
        }
        i_ptr_prev = i_ptr;
        i_ptr = i_ptr->get_next();

    }
    return false;
}

//

Object_label::Object_label(\
    int pos_x, int pos_y, int size_x, int size_y, \
    int id, int speed, int probabilistic_movement) : pos_x(pos_x), pos_y(pos_y), \
        size_x(size_x), size_y(size_y), id(id), speed(speed), \
        probabilistic_movement(probabilistic_movement)
{
    form_visual = new QLabel("");
    form_visual->setGeometry(pos_x, pos_y, size_x, size_y);
    std::string style_obj = "background-color : " + random_color_16_str();
    //form_visual->setStyleSheet("background-color : #DAA520");
    form_visual->setStyleSheet(QString::fromStdString(style_obj));

    list_points = new ListPoints(pos_x, pos_y);

}

Object_label::~Object_label(){
    delete form_visual;
}

//случайное движение
void Object_label::random_walk(int map_size_x, int map_size_y){

    int direction = rand() % probabilistic_movement;
    int x_move = 0, y_move = 0;
    if(direction == 0){
        if(pos_x + speed <= map_size_x){
            x_move = speed;
        }
    }
    else if(direction == 1){
        if(pos_x - speed >= 0){
            x_move = -1 * speed;
        }
    }
    else if(direction == 2){
        if(pos_y + speed <= map_size_y){
            y_move = speed;
        }
    }
    else if(direction == 3){
        if(pos_y - speed >= 0){
            y_move = -1 * speed;
        }
    }
    if(x_move != 0 || y_move != 0){
        pos_x += x_move;
        pos_y += y_move;
        list_points->addPoints(pos_x, pos_y);
    }

}
//вернуть характеристики объекта в виде строки
std::string Object_label::return_info_params(){
    std::string parameters = "x = ";
    parameters += std::to_string(pos_x);
    parameters += " y = " + std::to_string(pos_y);
    parameters += ", size("+std::to_string(size_x)+" "+std::to_string(size_y)+")";
    parameters += "\nID = " + std::to_string(id) + " speed = "+std::to_string(speed);
    parameters += " count points = "+std::to_string(list_points->get_count_points());
    parameters += "\ndistance = " + std::to_string(return_distance_current());
    return parameters;
}
//проверить нахождение курсора мыши в пределах размера объекта
//потом добавить учитывание маштаба
bool Object_label::return_cursor_touch(int x_cursor, int y_cursor){
    if((x_cursor >= pos_x && x_cursor <= pos_x+size_x) && \
    (y_cursor >= pos_y && y_cursor <= pos_y+size_y))
    {
        std::cout<<"\tid = "<<id<<std::endl;
        return true;
    }
    return false;


}


//перерисовать объект согласно масштабу
void Object_label::draw(int x_new, int y_new, int scale){

    int new_size_x = add_percentage(size_x, scale);
    int new_size_y = add_percentage(size_y, scale);
    int new_pos_x = x_new + add_percentage(pos_x, scale);
    int new_pos_y = y_new + add_percentage(pos_y, scale);
    form_visual->setGeometry(new_pos_x, new_pos_y, new_size_x, new_size_y);

    //std::cout<<"new x = "<<new_size_x<<"  new y = "<<new_size_y<<std::endl;
    //std::cout<<"id draw - "<<id<<std::endl;
}

int Object_label::return_distance_to_object(Object_label *ptr_object){
    if(!ptr_object){
        std::cout<<"Error: the object does not exist"<<std::endl;
        return -1;
    }
    int dist = distance_points(pos_x, pos_y, ptr_object->pos_x, ptr_object->pos_y);
    std::cout<<"id = "<<ptr_object->id<<std::endl;
    std::cout<<"\tdist = "<<dist<<std::endl;
    return dist;

}

int Object_label::return_distance_to_point(int x, int y){

    int dist = distance_points(pos_x, pos_y, x, y);

    return dist;
}
//оптимизация: рассчитывать расст сразу при добавление новой точки
int Object_label::return_distance_current(){
    if(list_points->get_count_points() == 1){
        return 0;
    }

    int i = 0;
    int dist = 0;
    Stack_points_xy *iter_point = list_points->head_stack->get_next(), *iter_point_2 = list_points->head_stack;

    while(iter_point){
        //std::cout<<"\t\ti = "<<i<<std::endl;
        dist += distance_points(\
            iter_point_2->get_x(), iter_point_2->get_y(), iter_point->get_x(), iter_point->get_y());
        //std::cout<<"\t\tdist = "<<dist<<std::endl;
        iter_point_2 = iter_point;
        iter_point = iter_point->get_next();
        i++;
    }
    return dist;

}



int Object_label::get_id(){
    return id;
}
int Object_label::get_size_x(){
    return size_x;
}
int Object_label::get_size_y(){
    return size_y;
}
int Object_label::get_speed(){
    return speed;
}
int Object_label::get_pos_x(){
    return pos_x;
}
int Object_label::get_pos_y(){
    return pos_y;
}






