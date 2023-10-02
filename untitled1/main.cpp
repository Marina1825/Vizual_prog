#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1000, 1000);
    w.show();
    /*1 пиксиль = 10 см*/
    return a.exec();
}
