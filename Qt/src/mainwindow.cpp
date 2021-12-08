#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , trayIcon(new QSystemTrayIcon(this))
    , trayIconMenu(new QMenu(this))
    , close_flag(false)
{
    ui->setupUi(this);
    setup_tray();

//    connect(device, &HID_Interface::resultReady, this, &MainWindow::updateData);
//    connect(device, &HID_Interface::connection_status, this, &MainWindow::connectedMode);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::shutdown);
    connect(ui->actionGitHub, &QAction::triggered, this, &MainWindow::github);
    connect(ui->actionAbout_this_app , &QAction::triggered, this, &MainWindow::about);
    connect(ui->cpuSlider, &QAbstractSlider::valueChanged, this, &MainWindow::sendData);
    connect(ui->gpuSlider, &QAbstractSlider::valueChanged, this, &MainWindow::sendData);
    connect(ui->turboButton, &QAbstractButton::pressed, this, &MainWindow::turbo);
    connect(ui->quietButton, &QAbstractButton::pressed, this, &MainWindow::quiet);
    connect(ui->offButton, &QAbstractButton::pressed, this, &MainWindow::off);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    device_worker.start();
}


MainWindow::~MainWindow()
{
    delete ui;
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
    QAction * turbo_action = new QAction("Turbo Mode", this);
    QAction * quiet_action = new QAction("Quiet Mode", this);
    QAction * off_action = new QAction("Off fans", this);
    QAction * quit_action = new QAction("Exit", this);

    // connect signals
    connect(turbo_action, &QAction::triggered, this, &MainWindow::turbo);
    connect(quiet_action, &QAction::triggered, this, &MainWindow::quiet);
    connect(off_action, &QAction::triggered, this, &MainWindow::off);
    connect(quit_action, &QAction::triggered, this, &MainWindow::shutdown);

    // add menu
    trayIconMenu->addAction(turbo_action);
    trayIconMenu->addAction(quiet_action);
    trayIconMenu->addAction(off_action);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quit_action);

    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();
}


void MainWindow::closeEvent(QCloseEvent * event)
{
    if(false == this->close_flag)
    {
        event->ignore();
        this->hide();
    }
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
}

void MainWindow::updateData(const slave_mess_t &data)
{
    QString text;

    text = QString::number(data.cpu_fan_speed) + QString(" RPM");
    ui->cpuLcd->setText(text);

    text = QString::number(data.gpu_fan_speed) + QString(" RPM");
    ui->gpuLcd->setText(text);
}

void MainWindow::sendData()
{
    master_mess_t mess =
    {
        .cpu_setpoint = (uint16_t)ui->cpuSlider->value(),
        .gpu_setpoint = (uint16_t)ui->gpuSlider->value()
    };

//    device->write(mess);
}

void MainWindow::cpuPercentage(int percentage) {
    ui->cpuProgressBar->setValue(percentage);
}

void MainWindow::gpuPercentage(int percentage) {
    ui->gpuProgressBar->setValue(percentage);
}

void MainWindow::turbo()
{
    ui->cpuSlider->setValue(100);
    ui->gpuSlider->setValue(100);
}

void MainWindow::quiet()
{
    ui->cpuSlider->setValue(30);
    ui->gpuSlider->setValue(30);
}

void MainWindow::off()
{
    ui->cpuSlider->setValue(0);
    ui->gpuSlider->setValue(0);
}
