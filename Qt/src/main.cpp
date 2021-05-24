#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QResource::registerResource("/home/mbober/Documents/RoboVision/resources.rcc");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
