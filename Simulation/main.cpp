#include "mainwindow.h"

#include <QApplication>

#include <ctime>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i;
    for(i = 0; i < argc; ++i){
        printf("%s\n", argv[i]);
    }
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
