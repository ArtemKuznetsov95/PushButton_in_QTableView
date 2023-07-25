#ifndef CUSTOMHEADERVIEW_H
#define CUSTOMHEADERVIEW_H

#include <QHeaderView>
#include <QPainter>
#include <QPushButton>
#include <QStyleOptionButton>
#include <QApplication>
///
/// \brief The CustomHeaderView class - Класс ручного редактирования заголовка таблицы
///
class CustomHeaderView : public QHeaderView
{
public:
    CustomHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr);
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;
};

#endif // CUSTOMHEADERVIEW_H
