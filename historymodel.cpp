#include "historymodel.h"

HistoryModel::HistoryModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    HistoryStruct s;
    s.number= "123567890";
    s.type = 0;
    history.push_back(s);
    s.type = 1;
    history.push_back(s);
}

int HistoryModel::rowCount(const QModelIndex &/*parent*/) const{
    return history.size();
}

int HistoryModel::columnCount(const QModelIndex &/*parent*/) const{
    return 2;
}

QVariant HistoryModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation==Qt::Horizontal){
        if(role==Qt::DisplayRole){
            switch(section){
                case 0:
                    return "Numer";
                case 1:
                    return "Status";
            }
        }
    }
    return QVariant();
}

QVariant HistoryModel::data(const QModelIndex &index, int role) const{
    if(role==Qt::DisplayRole){
        switch(index.column()){
            case 0:
                return history[index.row()].number.c_str();
            case 1:
                return QString::number(history[index.row()].type);
        }
    }
    return QVariant();
}

QStringList HistoryModel::mimeTypes() const{
    QStringList types;
    types << "text/plain";
    return types;
}

QMimeData* HistoryModel::mimeData(const QModelIndexList &indexes) const{

    QMimeData *mimeData = new QMimeData();

    /*foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            mimeData->setText(data(index, Qt::DisplayRole).toStringList()[2]);
        }
    }*/

    return mimeData;
}

void HistoryModel::addItem(HistoryStruct s){
    this->beginInsertRows(QModelIndex(), history.size(),history.size());
    history.push_back(s);
    this->endInsertRows();
}
