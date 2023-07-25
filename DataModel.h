#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
///
/// \brief The DataModel class - Класс переменных для таблицы
///
class DataModel
{
public:
    DataModel();

    int m_number;   //!< Номер точки
    QString m_x;    //!< Ширина
    QString m_y;    //!< Долгота
};

#endif // DATAMODEL_H
