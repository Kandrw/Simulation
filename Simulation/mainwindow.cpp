#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "distribution.hpp"
#include "simulationobject.hpp"

#include "output.hpp"

//#include <QtWidgets>
#include "QTimer"
#include <QMovie>
#include <QMouseEvent>
#include <QProcess>



#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>

#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Simulation");
    this->setFixedSize(size_window_weight, size_window_height);
    Output::initialization();
    initializationSimulationTimer();

    dist_sim = new Distribution(this);

    timer_stdout = new QTimer(this);

    connect(timer_stdout, SIGNAL(timeout()), this, SLOT( readOutputStdcout() ));
    timer_stdout->start(1);


    //std::cout<<"[Initialization MainWindow]"<<std::endl;
    Output::cout("[Initialization MainWindow]\n");
}

MainWindow::~MainWindow()
{
    delete dist_sim;
    delete ui;
    std::cout<<"[delete MainWindow]"<<std::endl;
    fclose(stdout);
}


void MainWindow::readOutputStdcout(){
    test++;
    std::string buf;
    buf += std::to_string(test) + "\n";
    buf += Output::get_and_delete_dec();
    ui->textEdit->setText(QString::fromStdString(buf));


}

void MainWindow::initializationSimulationTimer(){
    simulation_timer = new QTimer(this);
    connect(simulation_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    simulation_timer->stop();
    std::cout<<"Timer initialization"<<std::endl;
    //Output::cout("Timer initialization\n");
}

void MainWindow::onTimeout(){
    //std::cout<<"[==============]"<<std::endl;
    //std::cout<<"test = "<<test<<"\n";
    dist_sim->objs_random_walk();
    SimulationObject *ptr_obj = dist_sim->return_select_object();
    if(ptr_obj){
        std::string str_info = ptr_obj->get_info_parametrs();
        ui->label_info_object->setText(QString::fromStdString(str_info));
    }
    //Output::cout("[=-=-=-=-=-=]\n");
}

//-------------------------------------

// событие прокручивания
void MainWindow::wheelEvent(QWheelEvent *event){
    dist_sim->set_map_scale_wheel_y(event->angleDelta().y());
}
// событие мышки
void MainWindow::mouseMoveEvent(QMouseEvent *mouse){
    if(mouse->buttons() == Qt::LeftButton){
        dist_sim->move_simulation_by_mouse_pos(mouse->pos().rx(), mouse->pos().y());
    }

}
// событие нажатия кнопок мыши
void MainWindow::mousePressEvent(QMouseEvent *mouse){
    //
    if(mouse->buttons() == Qt::LeftButton){
        dist_sim->set_old_mouse_pos(mouse->pos().rx(), mouse->pos().y());
        SimulationObject *ptr_obj = dist_sim->selecting_an_object_by_cursor(mouse->pos().rx(), mouse->pos().y());
        if(ptr_obj){
            //std::cout<<"[TEST] yes\n";
            std::string str_info = ptr_obj->get_info_parametrs();
            ui->label_info_object->setText(QString::fromStdString(str_info));
        }


    }
}


//--------------------------------------

void MainWindow::on_exit_program_triggered()
{
    QApplication::exit();
}

void MainWindow::on_button_simulation_pause_clicked()
{
    //std::cout<<"Test pause - click"<<std::endl;
    Output::cout("Test pause - click\n");
    if(!pause_simulation){
        ui->button_simulation_pause->setText("Запуск");
        simulation_timer->stop();
    }
    else{
        ui->button_simulation_pause->setText("Пауза");
        simulation_timer->start(simulation_fps);
    }
    pause_simulation = !pause_simulation;
}

void MainWindow::on_button_create_obj_clicked()
{
    //std::cout<<"[button create]"<<std::endl;
    Output::cout("[button create]\n");
    dist_sim->create_new_object(1);
    //ui->label_count_object_all->setText(QString::fromStdString(count_object));
    std::string count_object = std::to_string(dist_sim->get_count_objs());
    ui->label_count_object_all->setText(QString::fromStdString(count_object));
}

void MainWindow::on_button_clear_object_all_clicked()
{
    dist_sim->delete_list_objects();
    ui->label_count_object_all->setText("0");
}

void MainWindow::on_button_map_simulation_center_clicked()
{
    dist_sim->set_map_scale(-20);
    dist_sim->set_map_pos(10, 100);
    dist_sim->render_scale_labels();

}

void MainWindow::on_button_delete_object_clicked()
{
    dist_sim->delete_select_obj_by_id();
    std::string count_object = std::to_string(dist_sim->get_count_objs());
    ui->label_count_object_all->setText(QString::fromStdString(count_object));
    ui->label_info_object->setText("Не выбран");
}

