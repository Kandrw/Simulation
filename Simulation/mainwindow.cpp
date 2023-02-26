#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simulation_objects.hpp"

#include <iostream>
#include <string>
#include <stdlib.h>

#include <QtWidgets>
#include "QTimer"
#include <QMovie>
#include <QMouseEvent>






MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(size_window_weight, size_window_height);
    this->setWindowTitle("Simulation");


    initializationSimulationMaps();
    initializationSimulationTimer();
    list_object = new Stack_object(nullptr);


    std::cout<<"[Initialization MainWindow]"<<std::endl;
}

MainWindow::~MainWindow()
{
    std::cout<<"[Delete MainWindow]"<<std::endl;
    delete ui;
}


void MainWindow::initializationSimulationMaps(){

    simulation_map = new QLabel();
    simulation_map->setGeometry(map_pos_x, map_pos_y, map_size_x, map_size_y);

    simulation_map->setStyleSheet("background-color : #808080");
    this->layout()->addWidget(simulation_map);
    simulation_map->lower();

}

void MainWindow::initializationSimulationTimer(){
    simulation_timer = new QTimer(this);
    connect(simulation_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    simulation_timer->stop();
    std::cout<<"Timer initialization"<<std::endl;
}

void MainWindow::onTimeout(){


    std::cout<<"[==============]"<<std::endl;
    Stack_object *i_stack_object = list_object->next;
    while(i_stack_object){
        i_stack_object->ptr_object->random_walk(map_size_x, map_size_y);
        i_stack_object->ptr_object->draw(map_pos_x, map_pos_y, map_scale);
        i_stack_object = i_stack_object->next;
    }

}
//событие нажатия кнопок мыши
void MainWindow::mousePressEvent(QMouseEvent *mouse){

    if(mouse->buttons() == Qt::LeftButton){
        std::cout<<"[T]click button\n";
        std::cout<<"x = "<<mouse->pos().rx()<<"y = "<<mouse->pos().ry()<<std::endl;

        Stack_object *i_stack_object = list_object->next;
        int global_pos_object_x, global_pos_object_y;

        while(i_stack_object){
            global_pos_object_x = map_pos_x + add_percentage(i_stack_object->ptr_object->pos_x, map_scale);
            global_pos_object_y = map_pos_y + add_percentage(i_stack_object->ptr_object->pos_y, map_scale);
            if((mouse->pos().rx() >= global_pos_object_x && \
                mouse->pos().rx() <= global_pos_object_x + i_stack_object->ptr_object->size_x) && \
                (mouse->pos().ry() >= global_pos_object_y && \
                mouse->pos().ry() <= global_pos_object_y + i_stack_object->ptr_object->size_y)){
                ui->label_info_object->setText(QString::fromStdString(
                            i_stack_object->ptr_object->return_info_params()));
                id_delete_by_clicking = i_stack_object->id;
                break;
            }
            i_stack_object = i_stack_object->next;
        }

    }



    if(mouse->buttons() == Qt::LeftButton && \
            (mouse->pos().rx() >= map_pos_x && mouse->pos().rx() <= map_pos_x + add_percentage(map_size_x, map_scale)) &&\
            (mouse->pos().ry() >= map_pos_y && mouse->pos().ry() <= map_pos_y + add_percentage(map_size_y, map_scale)))
    {
        old_pos_mause_x = mouse->pos().rx();
        old_pos_mause_y = mouse->pos().ry();

    }
    else{
        old_pos_mause_x = 0;
        old_pos_mause_y = 0;
    }

}
//событие прокручивания
void MainWindow::wheelEvent(QWheelEvent *ev){

    if(ev->angleDelta().y() > 0 && map_scale < 200){
        map_scale += size_factor;
        int new_map_size_x = add_percentage(map_size_x, map_scale);
        int new_map_size_y = add_percentage(map_size_y, map_scale);


        simulation_map->setGeometry(map_pos_x, map_pos_y, new_map_size_x, new_map_size_y);

        Stack_object *i_ptr_stack = list_object->next;
        while(i_ptr_stack){
            i_ptr_stack->ptr_object->draw(map_pos_x, map_pos_y, map_scale);
            i_ptr_stack = i_ptr_stack->next;
        }

    }
    else if(ev->angleDelta().y() < 0 && map_scale > -80){
        map_scale -= size_factor;
        int new_map_size_x = add_percentage(map_size_x, map_scale);
        int new_map_size_y = add_percentage(map_size_y, map_scale);


        simulation_map->setGeometry(map_pos_x, map_pos_y, new_map_size_x, new_map_size_y);

        Stack_object *i_ptr_stack = list_object->next;
        while(i_ptr_stack){
            i_ptr_stack->ptr_object->draw(map_pos_x, map_pos_y, map_scale);
            i_ptr_stack = i_ptr_stack->next;
        }

    }

}
//событие мышки
void MainWindow::mouseMoveEvent(QMouseEvent *event){

    int new_pos_mouse_x, new_pos_mouse_y;
    if(event->buttons() == Qt::LeftButton && (old_pos_mause_x != 0 && old_pos_mause_y != 0)){
        new_pos_mouse_x = event->pos().rx() - old_pos_mause_x;
        new_pos_mouse_y = event->pos().ry() - old_pos_mause_y;
        old_pos_mause_x = event->pos().rx();
        old_pos_mause_y = event->pos().ry();

        map_pos_x += new_pos_mouse_x;
        map_pos_y += new_pos_mouse_y;

        Stack_object *i_ptr_stack = list_object->next;
        while(i_ptr_stack){
            i_ptr_stack->ptr_object->draw(map_pos_x, map_pos_y, map_scale);
            i_ptr_stack = i_ptr_stack->next;
        }

        int new_map_size_x = add_percentage(map_size_x, map_scale);
        int new_map_size_y = add_percentage(map_size_y, map_scale);

        simulation_map->setGeometry(map_pos_x, map_pos_y, new_map_size_x, new_map_size_y);
    }

}



void MainWindow::on_exit_program_triggered()
{
    QApplication::exit();
}

void MainWindow::on_button_pause_simulation_clicked()
{

    std::cout<<"Test pause - click"<<std::endl;
    if(!pause_simulation){
        ui->button_pause_simulation->setText("Запуск");
        simulation_timer->stop();
    }
    else{
        ui->button_pause_simulation->setText("Пауза");
        simulation_timer->start(simulation_fps);
    }
    pause_simulation = !pause_simulation;

}


void MainWindow::on_button_create_random_object_clicked()
{

    std::cout<<"Test create - click"<<std::endl;

    int pos_x_new_object = rand() % (map_size_x);
    int pos_y_new_object = rand() % (map_size_y);
    int size_x_new_object = 10 + (rand() % 20);
    int size_y_new_object = 10 + (rand() % 20);
    int speed = 1 + (rand() % 20);
    int id = Create_id_object(list_object);
    int probabilistic_movement = 4 + (rand() % 20);
    Object_label *new_object_label = new Object_label(\
                pos_x_new_object, pos_y_new_object, size_x_new_object, size_y_new_object,\
                id, speed, probabilistic_movement);

    new_object_label->draw(map_pos_x, map_pos_y, map_scale);
    insert_list_object(list_object, new_object_label);
    std::string count_object = std::to_string(list_object->id);
    ui->label_count_object_all->setText(QString::fromStdString(count_object));
    this->layout()->addWidget(new_object_label->form_visual);
    new_object_label->form_visual->lower();
    simulation_map->stackUnder(new_object_label->form_visual);

}


void MainWindow::on_button_clear_object_all_clicked()
{

    std::cout<<"Test clear - click"<<std::endl;
    Stack_object *i_ptr = list_object->next, *i_ptr_clear;
    while(i_ptr){
        i_ptr_clear = i_ptr;
        i_ptr = i_ptr->next;
        this->layout()->removeWidget(i_ptr_clear->ptr_object->form_visual);
        delete i_ptr_clear->ptr_object;
        delete i_ptr_clear;
    }
    list_object->id = 0;
    list_object->next = nullptr;
    ui->label_count_object_all->setText(QString::fromStdString("0"));

}

void MainWindow::on_button_delete_object_clicked()
{
    if(id_delete_by_clicking != 0){
        Object_label *delete_ptr_object = search_id_object_list(list_object, id_delete_by_clicking );
        if(delete_ptr_object){
            this->layout()->removeWidget(delete_ptr_object->form_visual);
            if(delete_object_list_by_id(list_object, id_delete_by_clicking)){
                std::cout<<"delete "<<id_delete_by_clicking<<std::endl;
            }
            else{
                std::cout<<"not found id "<<id_delete_by_clicking<<std::endl;
            }

            id_delete_by_clicking = 0;
            std::string count_title = std::to_string(list_object->id);
            ui->label_count_object_all->setText(QString::fromStdString(count_title));
            ui->label_info_object->setText("Объект на выбран");
        }
    }

}

void MainWindow::on_button_map_simulation_center_clicked()
{

    map_pos_x = 10;
    map_pos_y = 100;
    map_scale = 0;
    simulation_map->setGeometry(map_pos_x, map_pos_y, map_size_x, map_size_y);
    Stack_object *i_ptr_stack = list_object->next;
    while(i_ptr_stack){
        i_ptr_stack->ptr_object->draw(map_pos_x, map_pos_y, map_scale);
        i_ptr_stack = i_ptr_stack->next;
    }

}

