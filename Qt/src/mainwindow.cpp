#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , device(new Serial)
    , trayIcon(new QSystemTrayIcon(this))
    , trayIconMenu(new QMenu(this))
    , close_flag(false)
{
    ui->setupUi(this);
    setup_tray();
    autoconnect();


    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::actionConnect);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::actionDisconnect);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::shutdown);
    connect(ui->actionGitHub, &QAction::triggered, this, &MainWindow::github);
    connect(ui->actionAbout_this_app , &QAction::triggered, this, &MainWindow::about);
    connect(device, &Serial::cpuSpeedChanged, this,  &MainWindow::cpuSpeed);
    connect(device, &Serial::gpuSpeedChanged, this,  &MainWindow::gpuSpeed);
    connect(device, &Serial::cpuPercentageChanged, this,  &MainWindow::cpuPercentage);
    connect(device, &Serial::gpuPercentageChanged, this,  &MainWindow::gpuPercentage);
    connect(ui->cpuSlider, &QAbstractSlider::valueChanged, device, &Serial::setCpuFanSpeed);
    connect(ui->gpuSlider, &QAbstractSlider::valueChanged, device, &Serial::setGpuFanSpeed);
    connect(ui->turboButton, &QAbstractButton::pressed, this, &MainWindow::turbo);
    connect(ui->quietButton, &QAbstractButton::pressed, this, &MainWindow::quiet);
    connect(ui->offButton, &QAbstractButton::pressed, this, &MainWindow::off);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

}



void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
            if(this->isVisible())
            {
                this->hide();
            }
            else
            {
                this->show();
            }

            break;

    default:
        break;
    }
}


void MainWindow::shutdown()
{
    this->close_flag = true;
    this->close();
}


void MainWindow::setup_tray()
{
    // setup icon
    trayIcon->setIcon(QIcon(":/icon/icons/fan_white.png"));
    trayIcon->setToolTip("Cooling App");

    // create menu
    QAction * view_action = new QAction("Launch Cooling App", this);
    QAction * turbo_action = new QAction("Turbo Mode", this);
    QAction * quiet_action = new QAction("Quiet Mode", this);
    QAction * off_action = new QAction("Off fans", this);
    QAction * quit_action = new QAction("Exit", this);

    // connect signals
    connect(view_action, &QAction::triggered, this, &MainWindow::show);
    connect(turbo_action, &QAction::triggered, this, &MainWindow::turbo);
    connect(quiet_action, &QAction::triggered, this, &MainWindow::quiet);
    connect(off_action, &QAction::triggered, this, &MainWindow::off);
    connect(quit_action, &QAction::triggered, this, &MainWindow::shutdown);

    // add menu
    trayIconMenu->addAction(view_action);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(turbo_action);
    trayIconMenu->addAction(quiet_action);
    trayIconMenu->addAction(off_action);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quit_action);

    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();
}


void MainWindow::autoconnect()
{
    QString devicePort = device->findKnownDevice(device->getDevices());

    if(!devicePort.isEmpty())
    {
        if(device->connect(devicePort))
        {
            this->connectedMode(true);
        }
    }
    else
    {
        this->connectedMode(false);
    }
}


void MainWindow::closeEvent(QCloseEvent * event)
{
    if(false == this->close_flag)
    {
        event->ignore();
        this->hide();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


/**
 * Connect to server slot.
 */
void MainWindow::actionConnect() {
    ConnectionDialog dialog(device->getDevices());
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
    QDesktopServices::openUrl(QUrl("https://github.com/mbober1/ESPCooling", QUrl::TolerantMode));
}


/**
 * Display the popup about dialog 
 */
void MainWindow::about() {
    AboutDialog dialog;
    dialog.setModal(true);
    dialog.exec();
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

    ui->turboButton->setEnabled(state);
    ui->quietButton->setEnabled(state);
    ui->offButton->setEnabled(state);

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

void MainWindow::turbo() {
    ui->cpuSlider->setValue(100);
    ui->gpuSlider->setValue(100);
}

void MainWindow::quiet() {
    ui->cpuSlider->setValue(30);
    ui->gpuSlider->setValue(30);
}

void MainWindow::off() {
    ui->cpuSlider->setValue(0);
    ui->gpuSlider->setValue(0);
}