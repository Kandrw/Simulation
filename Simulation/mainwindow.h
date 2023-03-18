#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Distribution;

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
    void mousePressEvent(QMouseEvent *mouse);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *mouse);

private slots:

    void onTimeout();

    void on_exit_program_triggered();

    void on_button_simulation_pause_clicked();

    void on_button_create_obj_clicked();

    void on_button_clear_object_all_clicked();

    void on_button_map_simulation_center_clicked();

    void on_button_delete_object_clicked();

private:
    Ui::MainWindow *ui;

    int size_window_height = 800;
    int size_window_weight = 1000;
    bool pause_simulation = true;
    int simulation_fps = 60;

    QTimer *simulation_timer;

    Distribution *dist_sim = nullptr;

private:
    void initializationSimulationTimer();

};

#endif // MAINWINDOW_H
