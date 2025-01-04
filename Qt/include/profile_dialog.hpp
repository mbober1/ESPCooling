#ifndef PROFILE_DIALOG_HPP
#define PROFILE_DIALOG_HPP

#include <QDialog>
#include <QFile>
#include "include/types.h"
#include <QSlider>

namespace Ui
{
class profile_dialog;
}


typedef struct
{
    QPushButton* button;
    QSlider* cpu_slider;
    QSlider* gpu_slider;

} profile_t;


class profile_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit profile_dialog(QWidget *parent = nullptr, QString filename = "confgi.bin");
    ~profile_dialog();

public slots:
    void setColour(QPushButton* button);
    bool save_file();

private:
    Ui::profile_dialog* ui;
    QFile* file;
    Config_t config;
    profile_t* profiles;

    QColor getColour();
    Config_t read_file();
    bool write_file(Config_t &config);
    Colours_t toColour(QPushButton* button);
};

#endif // PROFILE_DIALOG_HPP
