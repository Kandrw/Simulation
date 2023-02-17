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

    std::cout<<"[Create MainWindow]"<<std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exit_program_triggered()
{
    QApplication::exit();
}



void MainWindow::on_button_pause_simulation_clicked()
{
    std::cout<<"Test pause - click"<<std::endl;
}


void MainWindow::on_button_create_random_object_clicked()
{
    std::cout<<"Test create - click"<<std::endl;
}


void MainWindow::on_button_clear_object_all_clicked()
{
    std::cout<<"Test clear - click"<<std::endl;
}

