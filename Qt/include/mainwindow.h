#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include "connectiondialog.h"
#include "aboutdialog.h"
#include <QtSerialPort>
#include "serial.hpp"
#include "thread.hpp"

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
    void github();
    void about();
    void turbo();
    void quiet();
    void off();
    void cpuPercentage(int percentage);
    void gpuPercentage(int percentage);
    void connectedMode(bool state);
    void updateData(const slave_mess_t &data);
    void sendData();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void shutdown();
    void setup_tray();

private:

    Ui::MainWindow *ui;
    Thread device_worker;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    bool close_flag;
};
#endif // MAINWINDOW_H
