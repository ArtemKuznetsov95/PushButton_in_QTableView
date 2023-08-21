#include "CustomDelegateView.h"
#include <QApplication>

CustomDelegateView::CustomDelegateView(QObject *parent) :
    QItemDelegate(parent)
{

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
    if(event->type() == QEvent::MouseButtonRelease && index.column() == 3) {
        emit signalClicked(index);
    }
    else
        QItemDelegate::editorEvent(event, model, option,index);
    return true;
}
