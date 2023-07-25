#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <../DataModel.h>
#include <QPushButton>
///
/// \brief The TableModel class - Класс модели для таблицы
///
class TableModel : public QAbstractTableModel
{
    Q_OBJECT
signals:
    ///
    /// \brief dataUpdated - Сигнал обновления модели
    ///
    void dataUpdated();
public:
    TableModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index = QModelIndex(), int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    ///
    /// \brief updateModel  - Функция обновляет данные модели
    ///
    void updateModel();
    ///
    /// \brief deleted      - Функция удаления записи в модели
    /// \param indexRow     - Индекс строки для ее удаления
    ///
    void deleted(int indexRow);
    ///
    /// \brief append       - Функция добавления строки в модели
    ///
    void append();

private:
    QList<DataModel> m_list;    //!< Список данных модели отображающихся в таблице
};

#endif // TABLEMODEL_H
