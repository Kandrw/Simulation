#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTimer;
class QLabel;
class Stack_object;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int size_window_height = 800;
    int size_window_weight = 1000;

    int map_pos_x = 10;
    int map_pos_y = 100;
    int map_size_x = 1000;
    int map_size_y = 1000;






public:
    bool pause_simulation = true;
    int simulation_fps = 60;
    int id_delete_by_clicking = 0;

    int old_pos_mause_x = 0;
    int old_pos_mause_y = 0;

    int size_factor = 10;
    int map_scale = 0;

public:
    QTimer *simulation_timer;
    QLabel *simulation_map;
    Stack_object *list_object;

private:
    void initializationSimulationMaps();
    void initializationSimulationTimer();

    void mousePressEvent(QMouseEvent *mouse);
    void wheelEvent(QWheelEvent *ev);
    void mouseMoveEvent(QMouseEvent *event);

private slots:


    void onTimeout();

    void on_exit_program_triggered();

    void on_button_pause_simulation_clicked();

    void on_button_create_random_object_clicked();

    void on_button_clear_object_all_clicked();

    void on_button_delete_object_clicked();

    void on_button_map_simulation_center_clicked();

private:
    Ui::MainWindow *ui;
};




#endif // MAINWINDOW_H
