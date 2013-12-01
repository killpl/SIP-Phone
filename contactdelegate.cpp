#include "contactdelegate.h"

ContactDelegate::ContactDelegate(QObject *parent):QStyledItemDelegate(parent)
{
}

void ContactDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{

    QRect r = option.rect;
    if(option.state & QStyle::State_Selected){
        painter->setBrush(QBrush(QColor(200,200,200,100)));
    } else{
        painter->setBrush(QBrush(QColor(100,100,100,100)));
    }
    painter->drawRoundedRect(QRect(r.x()+1, r.y()+1, r.width()-2, r.height()-2),3,3);
    painter->setBrush(QBrush(QColor(255,0,0,255)));

    QStringList data = index.data().toStringList();

    painter->setFont(QFont("serif",10));
    painter->drawText(QRect(r.x()+5,r.y()+3,r.width()-10, r.height()-10),data[0]);

    painter->setFont(QFont("serif",10));
    painter->drawText(QRect(r.x()+5,r.y()+18,r.width()-10, r.height()-10),data[1]);

    painter->setFont(QFont("serif",18,2));
    painter->drawText(QRect(r.x()+220,r.y()+5,r.width()-10, r.height()-10),data[2]);

}

QSize ContactDelegate::sizeHint(const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const{
    return QSize(100,40);
}
