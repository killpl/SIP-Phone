#ifndef CONTACTDELEGATE_H
#define CONTACTDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QBrush>
#include <QStringList>

class ContactDelegate : public  QStyledItemDelegate
{
public:
    ContactDelegate(QObject* parent);

private:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // CONTACTDELEGATE_H
