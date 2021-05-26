#include "connectiondialog.h"
#include "ui_connectiondialog.h"


/**
 * A constructor.
 * @param[in,out] parent QWidget type parent.
 */
ConnectionDialog::ConnectionDialog(QList<QSerialPortInfo> devices, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

    for (size_t i = 0; i < devices.count(); i++)
    {
        ui->comboBox->addItem(devices.at(i).portName() + " - " + devices.at(i).description());
    }
    
}

/**
 * A destructor.
 */
ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

/**
 * Get adress for connection.
 * @return Address of device.
 */
QString ConnectionDialog::getAdress() {
    return ui->comboBox->currentText().split(" ").first();
}