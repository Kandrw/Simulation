#include "mainwindow.h"
#include "ui_mainwindow.h"


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
}


void MainWindow::on_button_clear_object_all_clicked()
{
    std::cout<<"Test clear - click"<<std::endl;
}

