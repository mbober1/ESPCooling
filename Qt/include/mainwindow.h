#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include "connectiondialog.h"
#include <QtSerialPort>
#include "serial.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void actionConnect();
    void actionDisconnect();
    void github();
    void about();
    void cpuSpeed(int speed);
    void gpuSpeed(int speed);
    void connectedMode(bool state);

private:
    Ui::MainWindow *ui;
    Serial *device;
};
#endif // MAINWINDOW_H
