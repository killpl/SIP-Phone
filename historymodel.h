#ifndef HISTORYMODEL_H
#define HISTORYMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QStringList>
#include <QMimeData>

#include "structs.h"

class HistoryModel : public QAbstractTableModel
{
    Q_OBJECT

    QVector<HistoryStruct> history;
public:

    explicit HistoryModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;

    Qt::DropActions supportedDragActions();
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QStringList mimeTypes() const;
    QMimeData* mimeData(const QModelIndexList &indexes) const;

    void addItem(HistoryStruct s);

signals:
    
public slots:
    
};

#endif // HISTORYMODEL_H
