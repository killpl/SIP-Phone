#include "contactsmodel.h"

ContactsModel::ContactsModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    ContactStruct s;
    s.email = "aaaa";
    s.name="bbb";
    s.number = "54353535";

    contacts.insert(s.number,s);
    s.email="cccccc";
    s.name="zzzzzz";
    s.number="5234234234";
    contacts.insert(s.number, s);
}

int ContactsModel::rowCount(const QModelIndex &/*parent*/) const
{
    return contacts.size();
}

int ContactsModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1;
}

QVariant ContactsModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role == Qt::DisplayRole)
         {
             if (orientation == Qt::Horizontal) {
                 switch (section)
                 {
                 case 0:
                     return QString("Kontakt");
                 /*case 1:
                     return QString("Adres email");
                 case 2:
                     return QString("Numer telefonu");*/
                 }
             }
         }
         return QVariant();
}

QVariant ContactsModel::data(const QModelIndex &index, int role) const
{
    if(role==Qt::DisplayRole)
    {
        ContactStruct s = (contacts.begin()+index.row()).value();
        QStringList list;
        list.append(QString(s.name.c_str()));
        list.append(QString(s.email.c_str()));
        list.append(QString(s.number.c_str()));

        switch(index.column()){
            case 0:
                return QVariant(list);//QString(s.name.c_str());
            /*case 1:
                return QString(s.email.c_str());
            case 2:
                return QString(s.number.c_str());
            default:
                return QString("Error");*/
        }
        //return QString("Kontakt %1 (%2)").arg(index.row()+1).arg(index.column()+1);
    }
    return QVariant();

}


void ContactsModel::addContact(ContactStruct c){
    contacts.insert(c.number, c);
}

Qt::DropActions ContactsModel::supportedDragActions(){
     return Qt::CopyAction | Qt::MoveAction;
}

Qt::ItemFlags ContactsModel::flags(const QModelIndex &index) const{
        Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);

        if (index.isValid())
            return Qt::ItemIsDragEnabled | defaultFlags;
        else
            return Qt::ItemIsDropEnabled | defaultFlags;
}

QStringList ContactsModel::mimeTypes() const
{
    QStringList types;
    types << "text/plain";
    return types;
}

QMimeData* ContactsModel::mimeData(const QModelIndexList &indexes) const{

    QMimeData *mimeData = new QMimeData();

    foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            mimeData->setText(data(index, Qt::DisplayRole).toStringList()[2]);
        }
    }

    return mimeData;
}
