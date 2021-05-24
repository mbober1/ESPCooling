#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->device = new Serial;
    this->connectedMode(false);

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
        qDebug() << dialog.getAdress();
        if(device->connect(dialog.getAdress())) {
            this->connectedMode(true);
            return;
        }
    }
    
    this->connectedMode(false);
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

void MainWindow::connectedMode(bool state) {
    ui->actionConnect->setVisible(!state);
    ui->actionDisconnect->setVisible(state);
    ui->actionDisconnect->setEnabled(state);

    ui->cpuLabel->setEnabled(state);
    ui->cpuLayout->setEnabled(state);
    ui->cpuLcd->setEnabled(state);
    ui->cpuProgressBar->setEnabled(state);
    ui->cpuSlider->setEnabled(state);

    ui->gpuLabel->setEnabled(state);
    ui->gpuLayout->setEnabled(state);
    ui->gpuLcd->setEnabled(state);
    ui->gpuProgressBar->setEnabled(state);
    ui->gpuSlider->setEnabled(state);
}
