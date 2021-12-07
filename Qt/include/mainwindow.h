#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include "connectiondialog.h"
#include "aboutdialog.h"
#include <QtSerialPort>
#include "serial.hpp"

#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void actionConnect();
    void actionDisconnect();
    void github();
    void about();
    void turbo();
    void quiet();
    void off();
    void cpuSpeed(int speed);
    void cpuPercentage(int percentage);
    void gpuSpeed(int speed);
    void gpuPercentage(int percentage);
    void connectedMode(bool state);

    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void shutdown();
    void setup_tray();
    void autoconnect();
private:

    Ui::MainWindow *ui;
    Serial *device;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    bool close_flag;
};
#endif // MAINWINDOW_H
