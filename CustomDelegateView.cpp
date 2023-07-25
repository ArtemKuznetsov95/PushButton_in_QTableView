#include "CustomDelegateView.h"
#include <QApplication>
#include <QDebug>

CustomDelegateView::CustomDelegateView(QObject *parent) :
    QItemDelegate(parent)
{
    setClipping(true); //Отключение выделения ячейки
}

void CustomDelegateView::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::paint(painter, option, index);
    if(index.column() == 3) {
        QStyleOptionButton button;
        button.rect = QRect(option.rect.left()+1, option.rect.top()+1, option.rect.width() - 2, option.rect.height() - 2);
        button.features = QStyleOptionButton::None;
        button.text = "Удaлить точку";
        button.state = QStyle::State_Enabled;
        QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
    }
}

bool CustomDelegateView::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QItemDelegate::editorEvent(event, model, option,index);
    if(event->type() == QEvent::MouseButtonRelease && index.column() == 3) {       //При нажатии испускать сигнал
        emit signalClicked(index);
    }
    return true;
}
