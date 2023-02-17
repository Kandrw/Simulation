#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simulation_objects.hpp"

#include <iostream>
#include <string>
#include <stdlib.h>

#include <QtWidgets>
#include "QTimer"
#include <QMovie>


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
    map_size_x = size_window_weight - \
            (map_margin_from_edges_x_left + map_margin_from_edges_x_right);
    map_size_y = size_window_height - \
            (map_margin_from_edges_y_up + map_margin_from_edges_y_down);
    simulation_map = new QLabel();
    simulation_map->setGeometry(map_margin_from_edges_x_left,
                                map_margin_from_edges_y_up,
                                map_size_x, map_size_y);
    simulation_map->setStyleSheet("background-color : #808080");
    this->layout()->addWidget(simulation_map);
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
        i_stack_object->ptr_object->random_walk(
            map_margin_from_edges_x_left, map_margin_from_edges_x_left + map_size_x,
            map_margin_from_edges_y_up, map_margin_from_edges_y_up + map_size_y
                    );
        i_stack_object = i_stack_object->next;
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


    int pos_x_new_object = map_margin_from_edges_x_left + (rand() % (map_size_x - map_margin_from_edges_x_right));
    int pos_y_new_object = map_margin_from_edges_y_up + (rand() % (map_size_y - map_margin_from_edges_y_down));
    int size_x_new_object = 10 + (rand() % 100);
    int size_y_new_object = 10 + (rand() % 100);
    int speed = 1 + (rand() % 20);
    int id = Create_id_object(list_object);
    int probabilistic_movement = 4 + (rand() % 20);
    Object_label *new_object_label = new Object_label(
        pos_x_new_object, pos_y_new_object,
        size_x_new_object, size_y_new_object,
        id,speed, probabilistic_movement
        );

    insert_list_object(list_object, new_object_label);
    this->layout()->addWidget(new_object_label->form_visual);
    std::string count_object = std::to_string(list_object->id);
    ui->label_count_object_all->setText(QString::fromStdString(count_object));



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

