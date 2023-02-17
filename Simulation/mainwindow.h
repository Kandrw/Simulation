#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTimer;
class QLabel;
//class stack_object;

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

    int map_margin_from_edges_x_left = 10;
    int map_margin_from_edges_x_right = 10;
    int map_margin_from_edges_y_up = 100;
    int map_margin_from_edges_y_down = 100;

    int map_size_x;
    int map_size_y;





public:
    bool pause_simulation = true;
    int simulation_fps = 60;

public:
    QTimer *simulation_timer;
    QLabel *simulation_map;


private slots:
    void on_exit_program_triggered();

    void on_button_pause_simulation_clicked();

    void on_button_create_random_object_clicked();

    void on_button_clear_object_all_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
