#include "distribution.hpp"
#include "simulationmap.hpp"
#include "simulationobject.hpp"
#include "mainwindow.h"
#include "base_functions.hpp"

#include <QtWidgets>

#include <iostream>

Distribution::Distribution(MainWindow *mainwindow)
{
    std::cout<<"[Init Distribution]"<<std::endl;

    //map = new SimulationMap(1000, 1000, 10, 100);
    map = new GeoSimulationMap(1000, 1000, 0, 0, 83.1068);


    map_label = new QLabel("");
    map_label->setGeometry(map->get_posX(), map->get_posY(),
                           map->get_sizeX(), map->get_sizeY());
    map_label->setStyleSheet("background-color : #808080");

    this->mainwindow = mainwindow;
    mainwindow->layout()->addWidget(map_label);

}
Distribution::~Distribution(){
    std::cout<<"[Distribution] Delete dist..."<<std::endl;
    mainwindow->layout()->removeWidget(map_label);
    int i;
    for(i = 0; i < list_label_obj.size(); ++i){
        mainwindow->layout()->removeWidget(list_label_obj[i]);
        list_label_obj[i] = nullptr;
    }
    list_label_obj.clear();

    delete map;
    std::cout<<"[Distribution] Delete dist"<<std::endl;

}

void Distribution::create_new_object(int count){
    std::cout<<"[Distribution] create new obj..."<<std::endl;
    int i;
    SimulationObject *i_obj;
    for(i = 0; i < count; ++i){
        i_obj = map->create_new_object();
        if(i_obj){
            add_obj_list_label(i_obj);
        }
    }
    std::cout<<"[Distribution] create new obj"<<std::endl;
}
// Создание и добавление объекта QLabel в список
void Distribution::add_obj_list_label(SimulationObject *obj){
    std::cout<<"[Distribution] add label new obj..."<<std::endl;
    QLabel *new_label = new QLabel("");
    int pos_x, pos_y;
    int size_label_x, size_label_y;
    size_label_x = add_percentage(obj->get_size_x(), map_scale_sim);
    size_label_y = add_percentage(obj->get_size_y(), map_scale_sim);
    pos_x = map_label->geometry().x() + add_percentage(obj->get_pos_x(), map_scale_sim);
    pos_y = map_label->geometry().y() + add_percentage(obj->get_pos_y(), map_scale_sim);

    //new_label->setGeometry(\
        obj->get_pos_x() + map->get_posX(), obj->get_pos_y() + map->get_posY(), obj->get_size_x(), obj->get_size_y());
    new_label->setGeometry(pos_x, pos_y, size_label_x, size_label_y);
    std::string style_obj = "background-color : " + random_color_16_str();
    new_label->setStyleSheet(QString::fromStdString(style_obj));
    mainwindow->layout()->addWidget(new_label);
    list_label_obj.push_back(new_label);
    new_label->lower();
    map_label->stackUnder(new_label);

    std::cout<<"[Distribution] add label new obj"<<std::endl;
}
/*
void Distribution::add_obj_list_label(SimulationObject *obj){
    std::cout<<"[Distribution] add label new obj..."<<std::endl;
    QLabel *new_label = new QLabel("");
    int pos_x, pos_y;
    int size_label_x, size_label_y;
    size_label_x = add_percentage(obj->get_size_x(), map_scale_sim);
    size_label_y = add_percentage(obj->get_size_y(), map_scale_sim);
    pos_x = map_label->geometry().x() + add_percentage(obj->get_pos_x(), map_scale_sim);
    pos_y = map_label->geometry().y() + add_percentage(obj->get_pos_y(), map_scale_sim);

    //new_label->setGeometry(\
    //    obj->get_pos_x() + map->get_posX(), obj->get_pos_y() + map->get_posY(), obj->get_size_x(), obj->get_size_y());
    new_label->setGeometry(pos_x, pos_y, size_label_x, size_label_y);
    std::string style_obj = "background-color : " + random_color_16_str();
    new_label->setStyleSheet(QString::fromStdString(style_obj));
    mainwindow->layout()->addWidget(new_label);
    list_label_obj.push_back(new_label);
    new_label->lower();
    map_label->stackUnder(new_label);

    std::cout<<"[Distribution] add label new obj"<<std::endl;
}
*/
// Изменение масштаба
void Distribution::set_map_scale(int y){
    std::cout<<"[Distribution] set map scale..."<<std::endl;

    map_scale_sim = y;

    render_scale_labels();
    std::cout<<"[Distribution] set map scale"<<std::endl;
}
// Изменение масштаба(прокручиванием)
void Distribution::set_map_scale_wheel_y(int y){
    std::cout<<"[Distribution] set map scale..."<<std::endl;
    if(y > 0 && map_scale_sim < 200){
        map_scale_sim += size_factor;
    }
    else if(y < 0 && map_scale_sim > -80){
        map_scale_sim -= size_factor;
    }
    render_scale_labels();
    std::cout<<"[Distribution] set map scale"<<std::endl;
}

// Изменения размеров согласно масштабу
void Distribution::render_scale_labels(){
    std::cout<<"[Distribution] render_scale_labels..."<<std::endl;
    int new_size_label_x = add_percentage(map->get_sizeX(), map_scale_sim);
    int new_size_label_y = add_percentage(map->get_sizeY(), map_scale_sim);
    map_label->setGeometry(map->get_posX(), map->get_posY(), new_size_label_x, new_size_label_y);
    int i;
    int new_pos_x, new_pos_y;
    SimulationObject *i_ptr_obj;
    for(i = 0; i < list_label_obj.size(); ++i){
        i_ptr_obj = map->get_obj_by_index(i);
        new_size_label_x = add_percentage(i_ptr_obj->get_size_x(), map_scale_sim);
        new_size_label_y = add_percentage(i_ptr_obj->get_size_y(), map_scale_sim);
        new_pos_x = map_label->geometry().x() + add_percentage(i_ptr_obj->get_pos_x(), map_scale_sim);
        new_pos_y = map_label->geometry().y() + add_percentage(i_ptr_obj->get_pos_y(), map_scale_sim);
        list_label_obj[i]->setGeometry(new_pos_x, new_pos_y, new_size_label_x, new_size_label_y);
    }
    std::cout<<"[Distribution] render_scale_labels"<<std::endl;
}

// Сулчайное движение
void Distribution::objs_random_walk(){
    map->objects_random_walk();
    draw_labels();
}
// Перерисовка объекта по индексу
void Distribution::draw_label_by_index(int index){
    int pos_x, pos_y;
    int size_label_x, size_label_y;
    SimulationObject *obj = nullptr;
    if(index >= 0 && index < list_label_obj.size()){
        obj = map->get_obj_by_index(index);
        size_label_x = add_percentage(obj->get_size_x(), map_scale_sim);
        size_label_y = add_percentage(obj->get_size_y(), map_scale_sim);
        pos_x = map_label->geometry().x() + add_percentage(obj->get_pos_x(), map_scale_sim);
        pos_y = map_label->geometry().y() + add_percentage(obj->get_pos_y(), map_scale_sim);
        list_label_obj[index]->setGeometry(pos_x, pos_y, size_label_x, size_label_y);
    }
    else{
        std::cout<<"[Distribution] draw_label_by_index: out of range"<<std::endl;
    }
}
// Отрисовка объектов которые передвигались
void Distribution::draw_labels_objs_if_found_move(){
    int i;
    for(i = 0; i < list_label_obj.size(); ++i){
        if(map->get_obj_by_index(i)->get_found_move()){
            draw_label_by_index(i);
        }
    }
}
// Не доделана
void Distribution::draw_labels(){

    int i;
    for(i = 0; i < list_label_obj.size(); ++i){
        draw_label_by_index(i);

    }
}
// Сохранение позиции курсора для передвижения симуляции
void Distribution::set_old_mouse_pos(int x, int y){
    if( (x >= map->get_posX() && x <= map->get_posX() + add_percentage(map->get_sizeX(), map_scale_sim)) &&\
        (y >= map->get_posY() && y <= map->get_posY() + add_percentage(map->get_sizeY(), map_scale_sim)))
    {
        old_mouse_pos_x = x;
        old_mouse_pos_y = y;
    }
    else{
        old_mouse_pos_x = 0;
        old_mouse_pos_y = 0;
    }


}
// передвижение карты симуляции по позиции мыши
void Distribution::move_simulation_by_mouse_pos(int x, int y){

    if(old_mouse_pos_x != 0 || old_mouse_pos_y != 0){

        int delta_pos_mouse_x = x - old_mouse_pos_x;
        int delta_pos_mouse_y = y - old_mouse_pos_y;
        set_old_mouse_pos(x, y);
        map->set_posX(map->get_posX() + delta_pos_mouse_x);
        map->set_posY(map->get_posY() + delta_pos_mouse_y);
        render_scale_labels();
    }
}
// Удалить все объекты
void Distribution::delete_list_objects(){
    int i;
    for(i = 0; i < list_label_obj.size(); ++i){
        mainwindow->layout()->removeWidget(list_label_obj[i]);
        delete list_label_obj[i];
        list_label_obj[i] = nullptr;
    }
    list_label_obj.clear();
    map->delete_obj_all();
}
// Изменение масштаба
void Distribution::set_map_pos(int x, int y){
    map->set_posX(x);
    map->set_posY(y);
}

int Distribution::get_count_objs(){
    return map->get_count_obj();
}
// Проверка положения курсора на объектах
SimulationObject* Distribution::selecting_an_object_by_cursor(int x, int y){
    //Точка остановки работы
    int i;
    QLabel *i_ptr;
    for(i = 0; i < list_label_obj.size(); ++i){
        i_ptr = list_label_obj[i];
        if( (x >= i_ptr->pos().rx() && x <= i_ptr->geometry().x() + i_ptr->pos().rx()) &&\
            (y >= i_ptr->pos().ry() && y <= i_ptr->geometry().y() + i_ptr->pos().ry()) )
        {

            selected_object_id = map->get_obj_by_index(i)->get_id();
            return  map->get_obj_by_index(i);
        }
    }
    return nullptr;
}
/*
UserEquipment* Distribution::selecting_an_object_by_cursor(int x, int y){
    int i;
    QLabel *i_ptr;
    for(i = 0; i < list_label_obj.size(); ++i){
        i_ptr = list_label_obj[i];
        if( (x >= i_ptr->pos().rx() && x <= i_ptr->geometry().x() + i_ptr->pos().rx()) &&\
            (y >= i_ptr->pos().ry() && y <= i_ptr->geometry().y() + i_ptr->pos().ry()) )
        {

            selected_object_id = map->get_obj_by_index(i)->get_id();
            return  map->get_obj_by_index(i);
        }
    }
    return nullptr;
}
*/

void Distribution::delete_obj_by_id(int id){
    std::cout<<"[Distribution] delete_obj_by_id..."<<std::endl;
    int index = map->delete_obj_by_id(id);
    if(index >= 0){

        QLabel *ptr_label = list_label_obj[index];
        mainwindow->layout()->removeWidget(ptr_label);
        delete ptr_label;
        list_label_obj.erase(list_label_obj.cbegin() + index);
    }
    std::cout<<"[Distribution] delete_obj_by_id - "<<id<<std::endl;
}

void Distribution::delete_select_obj_by_id(){
    if(selected_object_id != 0){
        delete_obj_by_id(selected_object_id);
        selected_object_id = 0;
    }

}





