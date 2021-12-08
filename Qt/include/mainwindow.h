#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include "connectiondialog.h"
#include "aboutdialog.h"
#include <QtSerialPort>
#include "serial.hpp"
#include "include/hid_interface.hpp"

#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>



#define VENDOR_ID 0x483
#define PRODUCT_ID 0x91D1


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
    void github();
    void about();
    void turbo();
    void quiet();
    void off();
//    void cpuSpeed(int speed);
    void cpuPercentage(int percentage);
//    void gpuSpeed(int speed);
    void gpuPercentage(int percentage);
    void connectedMode(bool state);
    void updateData(const slave_mess_t &data);
    void sendData();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void shutdown();
    void setup_tray();
private:

    Ui::MainWindow *ui;
    HID_Interface *device;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    bool close_flag;
};
#endif // MAINWINDOW_H
