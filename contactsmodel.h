#ifndef CONTACTSMODEL_H
#define CONTACTSMODEL_H

#include <QAbstractTableModel>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QMimeData>

#include <structs.h>

#include <vector>
#include <iostream>

using namespace std;

class ContactsModel : public QAbstractTableModel
{
    Q_OBJECT

    QMap<string, ContactStruct> contacts;

public:
    explicit ContactsModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;

    Qt::DropActions supportedDragActions();
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QStringList mimeTypes() const;
    QMimeData* mimeData(const QModelIndexList &indexes) const;

    void addContact(ContactStruct c);
    string findContact(string number);
    void removeContact(QModelIndex index);

    QVector<ContactStruct> getContacts();
    
};

#endif // CONTACTSMODEL_H
