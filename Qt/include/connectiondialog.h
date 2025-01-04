#ifndef CONNECTIONDIALOG_HPP
#define CONNECTIONDIALOG_HPP

#include <QDialog>
#include <QtSerialPort>
#include <QTextList>

namespace Ui {
class ConnectionDialog;
}


/*!
*   \file 
*   \brief The file contains the pop-up dialog class.
*/

/**
    @brief Connection pop-up dialog class
*/
class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QList<QSerialPortInfo> devices, QWidget *parent = nullptr);
    ~ConnectionDialog();
    QString getAdress();

private:
    Ui::ConnectionDialog *ui;
};

#endif // CONNECTIONDIALOG_HPP
