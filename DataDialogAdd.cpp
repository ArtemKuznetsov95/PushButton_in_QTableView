#include "DataDialogAdd.h"
#include "ui_DataDialogAdd.h"

DataDialogAdd::DataDialogAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataDialogAdd)
{
    ui->setupUi(this);
}

DataDialogAdd::~DataDialogAdd()
{
    delete ui;
}

void DataDialogAdd::on_m_pushButton_add_clicked()
{
    QList<QPair<double, double>> listCoord;
    listCoord.append({ui->m_doubleSpinBox_x->value(), ui->m_doubleSpinBox_y->value()});
    emit dataTransmission(listCoord);

    close();
}

void DataDialogAdd::on_m_pushButton_close_clicked()
{
    close();
}
