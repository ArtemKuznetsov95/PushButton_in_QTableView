#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QMessageBox>
#include <TableModel.h>
#include <CustomHeaderView.h>
#include <CustomDelegateView.h>
#include <DataDialogAdd.h>

namespace Ui {
class Table;
}
///
/// \brief The Table class - Класс таблицы
///
class Table : public QWidget
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = nullptr);
    ~Table();

public slots:
    ///
    /// \brief createButton - Функция создания кнопок поверх ячеек
    ///
    void createButton();
    ///
    /// \brief onBtnClicked - Функция удаления строки
    /// \param index        - Индекс строки нажатой кнопки "Удаление точки"
    ///
    void onBtnClicked(QModelIndex index);
    ///
    /// \brief onSectionClicked - Функция добавления строки
    /// \param logicalIndex     - Индекс столбца
    ///
    void onSectionClicked(int logicalIndex);

private:
    Ui::Table *ui;
    TableModel* m_model;    //!< Ссылка на модель данных таблицы
};

#endif // TABLEMODEL_H
