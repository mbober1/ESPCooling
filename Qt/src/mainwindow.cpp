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
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::actionDisconnect);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionGitHub, &QAction::triggered, this, &MainWindow::github);
    connect(ui->actionAbout_this_app , &QAction::triggered, this, &MainWindow::about);
    connect(device, &Serial::cpuSpeedChanged, this,  &MainWindow::cpuSpeed);
    connect(device, &Serial::gpuSpeedChanged, this,  &MainWindow::gpuSpeed);
    connect(device, &Serial::cpuPercentageChanged, this,  &MainWindow::cpuPercentage);
    connect(device, &Serial::gpuPercentageChanged, this,  &MainWindow::gpuPercentage);
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
        if(device->connect(dialog.getAdress())) {
            this->connectedMode(true);
            return;
        }
    }
    
    this->connectedMode(false);
}


void MainWindow::actionDisconnect() {
    this->device->disconnect();
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
    ui->cpuLcd->setEnabled(state);
    ui->cpuProgressBar->setEnabled(state);
    ui->cpuSlider->setEnabled(state);
    ui->cpuSlider->setValue(0);

    ui->gpuLabel->setEnabled(state);
    ui->gpuLcd->setEnabled(state);
    ui->gpuProgressBar->setEnabled(state);
    ui->gpuSlider->setEnabled(state);
    ui->gpuSlider->setValue(0);

    ui->autoButton->setEnabled(state);
    ui->sendButton->setEnabled(state);
    ui->manualButton->setEnabled(state);

    this->cpuSpeed(0);
    this->cpuPercentage(0);
    this->gpuSpeed(0);
    this->gpuPercentage(0);
}

void MainWindow::cpuSpeed(int speed) {
    QString text = QString::number(speed) + QString(" RPM");
    ui->cpuLcd->setText(text);
}

void MainWindow::gpuSpeed(int speed) {
    QString text = QString::number(speed) + QString(" RPM");
    ui->gpuLcd->setText(text);
}

void MainWindow::cpuPercentage(int percentage) {
    ui->cpuProgressBar->setValue(percentage);
}

void MainWindow::gpuPercentage(int percentage) {
    ui->gpuProgressBar->setValue(percentage);
}