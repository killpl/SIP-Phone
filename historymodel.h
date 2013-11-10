#ifndef HISTORYMODEL_H
#define HISTORYMODEL_H

#include <QAbstractTableModel>

class HistoryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit HistoryModel(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // HISTORYMODEL_H
