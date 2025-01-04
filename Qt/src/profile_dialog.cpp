#include "include/profile_dialog.hpp"
#include "ui_profile_dialog.h"
#include <QColorDialog>



profile_dialog::profile_dialog(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::profile_dialog),
    file(new QFile(filename, this))
{
    ui->setupUi(this);

    profiles = new profile_t[PROFILES_COUNT]
    {
        { ui->colour_button_1, ui->cpu_slider_1, ui->gpu_slider_1 },
        { ui->colour_button_1, ui->cpu_slider_2, ui->gpu_slider_2 },
        { ui->colour_button_1, ui->cpu_slider_3, ui->gpu_slider_3 },
        { ui->colour_button_1, ui->cpu_slider_4, ui->gpu_slider_4 },
        { ui->colour_button_1, ui->cpu_slider_5, ui->gpu_slider_5 }
    };

    connect(ui->colour_button_2, &QPushButton::pressed, [this]() { setColour(ui->colour_button_2); });
    connect(ui->colour_button_3, &QPushButton::pressed, [this]() { setColour(ui->colour_button_3); });
    connect(ui->colour_button_4, &QPushButton::pressed, [this]() { setColour(ui->colour_button_4); });
    connect(ui->colour_button_5, &QPushButton::pressed, [this]() { setColour(ui->colour_button_5); });

    bool new_file;
    bool file_status;
    new_file = file->open(QIODevice::NewOnly);

    if(true == new_file)
    {
        Config_t data = {};
        this->write_file(data);
    }
    else
    {
        file_status = file->open(QIODevice::ReadWrite);

        if(true == file_status)
        {
            this->config = read_file();
        }
    }

}

profile_dialog::~profile_dialog()
{
    this->file->close();
    delete file;
    delete profiles;
    delete ui;
}


QColor profile_dialog::getColour()
{
    QColorDialog dialog(this);

    if(dialog.exec() == QDialog::Accepted)
    {
        return dialog.selectedColor();
    }
    else
    {
        return QColor();
    }
}


Config_t profile_dialog::read_file()
{
    Config_mess_t data;
    char* data_ptr = (char*)&data;
    int data_size = sizeof(Config_mess_t);
    int readed_data = this->file->read(data_ptr, data_size);

    if(readed_data == data_size)
    {
        return data.config;
    }
    else
    {
        Config_t blank_config = {};
        return blank_config;
    }
}


bool profile_dialog::write_file(Config_t &config)
{
    Config_mess_t data = {};
    char* data_ptr = (char*)&data;
    memcpy(&data.config, &config, sizeof(Config_t));
    int data_size = sizeof(Config_mess_t);
    int written_data = this->file->write(data_ptr, data_size);

    if(written_data == data_size)
    {
        return true;
    }
    else
    {
        return false;
    }

}

Colours_t profile_dialog::toColour(QPushButton* button)
{
    Colours_t data;
    QPalette palete = button->palette();
    QColor color = palete.color(QPalette::Button);
    data.red = color.red();
    data.blue = color.blue();
    data.green = color.green();
    return data;
}


void profile_dialog::setColour(QPushButton* button)
{
    QColor new_color = getColour();
    QPalette palete = button->palette();

    palete.setColor(QPalette::Button, new_color);
    button->setAutoFillBackground(true);
    button->setPalette(palete);
    button->update();
}

bool profile_dialog::save_file()
{

    for (size_t i = 0; i < PROFILES_COUNT; ++i)
    {
        this->config.profile[i].cpu_fan = this->profiles->cpu_slider->value();
        this->config.profile[i].gpu_fan = this->profiles->gpu_slider->value();
        this->config.profile[i].led = toColour(this->profiles->button);
    }

    return this->write_file(this->config);;
}
