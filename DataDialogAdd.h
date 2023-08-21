#ifndef DATADIALOGADD_H
#define DATADIALOGADD_H

#include <QDialog>
#include <QPair>

namespace Ui {
class DataDialogAdd;
}

class DataDialogAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DataDialogAdd(QWidget *parent = nullptr);
    ~DataDialogAdd();
signals:
    QList<QPair<double, double>> dataTransmission(QList<QPair<double, double>>);
private slots:
    void on_m_pushButton_add_clicked();

    void on_m_pushButton_close_clicked();

private:
    Ui::DataDialogAdd *ui;
};

#endif // DATADIALOGADD_H
