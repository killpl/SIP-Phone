#include "historymodel.h"

HistoryModel::HistoryModel(QObject *parent) :
    QAbstractTableModel(parent)
{
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

// 0 -inc
// 1 - out
// 2 - err
QVariant HistoryModel::data(const QModelIndex &index, int role) const{
    if(role==Qt::DisplayRole){
        switch(index.column()){
            case 0:
                return history[index.row()].number.c_str();

        }
    }

    if(role == Qt::DecorationRole){
        if(index.column()==1){
            if(history[index.row()].type==0)
                return QIcon(":/icons/icons/In.png");
            if(history[index.row()].type==1)
                return QIcon(":/icons/icons/Out.png");
            if(history[index.row()].type>1)
                return QIcon(":/icons/icons/Failure.png");
        }
    }

    return QVariant();
}

QStringList HistoryModel::mimeTypes() const{
    QStringList types;
    types << "text/plain";
    return types;
}

Qt::DropActions HistoryModel::supportedDragActions(){
     return Qt::CopyAction | Qt::MoveAction;
}

Qt::ItemFlags HistoryModel::flags(const QModelIndex &index) const{
        Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);

        if (index.isValid())
            return Qt::ItemIsDragEnabled | defaultFlags;
        else
            return Qt::ItemIsDropEnabled | defaultFlags;
}

QMimeData* HistoryModel::mimeData(const QModelIndexList &indexes) const{

    QMimeData *mimeData = new QMimeData();

    foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            mimeData->setText(history[index.row()].number.c_str());
        }
    }

    return mimeData;
}

void HistoryModel::addItem(HistoryStruct s){
    this->beginInsertRows(QModelIndex(), history.size(),history.size());
    history.push_back(s);
    this->endInsertRows();
}
