#include "connectiondialog.h"
#include "ui_connectiondialog.h"


/**
 * A constructor.
 * @param[in,out] parent QWidget type parent.
 */
ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
}

/**
 * A destructor.
 */
ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}