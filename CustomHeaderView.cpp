#include "CustomHeaderView.h"
#include <QDebug>

CustomHeaderView::CustomHeaderView(Qt::Orientation orientation, QWidget *parent) :
    QHeaderView(orientation, parent)
{
    setSectionsClickable(true); //true - заголовок будет реагировать на одиночные клики

}

void CustomHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    QHeaderView::paintSection(painter, rect, logicalIndex);                                     //Рисует заголовки по заданным по умолчании параметрамм

    //Если столбец == 3, в который мы хотим вставить кнопку
    if(logicalIndex == 3) {
        QStyleOptionButton option;                                                              //Опции для рисования кнопки
        option.rect = QRect(rect.left() + 1, rect.top() +1, rect.width()-2, rect.height()-2);   //Якоря для закрепления кнопки к ячейке
        option.features = QStyleOptionButton::None;                                             //Стиль кнопки классический
        option.text = "Добавить точку";
        QApplication::style()->drawControl(QStyle::CE_PushButton, &option, painter);            //Добавление кнопки с опциями в ячейку заголовка
    }
}
