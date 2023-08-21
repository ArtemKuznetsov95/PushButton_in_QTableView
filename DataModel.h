#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
///
/// \brief The DataModel class - Класс переменных для таблицы
///
class DataModel
{
public:
    DataModel(int number, double x, double y);

    int m_number;   //!< Номер точки
    double m_x;    //!< Ширина
    double m_y;    //!< Долгота
};

#endif // DATAMODEL_H
