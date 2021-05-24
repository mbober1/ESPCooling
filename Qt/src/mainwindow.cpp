#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::actionConnect);
    // connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::actionDisconnect);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionGitHub, &QAction::triggered, this, &MainWindow::github);
    connect(ui->actionAbout_this_app , &QAction::triggered, this, &MainWindow::about);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/**
 * Connect to server slot.
 */
void MainWindow::actionConnect() {
    ConnectionDialog dialog;
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted) {
        qDebug() << "dupa";
        // scene->resetPosition();
        // tcp.address = dialog.getAdress();
        // tcp.port = dialog.getTcpPort();
        // udp.address = dialog.getAdress();
        // udp.port = dialog.getUdpPort();
        // tcp.initConnection();
    }
}


/**
 * Open github link in browser
 */
void MainWindow::github() {
    // QDesktopServices::openUrl(QUrl("https://github.com/mbober1/RoboVision", QUrl::TolerantMode));
}


/**
 * Display the popup about dialog 
 */
void MainWindow::about() {
    // AboutProgramDialog dialog;
    // dialog.setModal(true);
    // dialog.exec();
}