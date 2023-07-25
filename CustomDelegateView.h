#ifndef CUSTOMDELEGATEVIEW_H
#define CUSTOMDELEGATEVIEW_H

#include <QObject>
#include <QItemDelegate>
///
/// \brief The CustomDelegateView class - Класс ручного добавления кнопок в таблицу
///
class CustomDelegateView : public QItemDelegate
{
    Q_OBJECT
signals:
    QModelIndex signalClicked(QModelIndex index);
public:
    CustomDelegateView(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

#endif // CUSTOMDELEGATEVIEW_H
