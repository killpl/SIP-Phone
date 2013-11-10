#ifndef REGISTRATIONSMODEL_H
#define REGISTRATIONSMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QColor>
#include <QIcon>

#include "structs.h"
#include "configuration.h"

class RegistrationsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit RegistrationsModel(QObject *parent = 0);

    QVector<RegistrationStruct> registrations;

    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;


    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;

    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;

    void addEmpty();
    void removeRow(QModelIndex &index);
    void addRegistration(RegistrationStruct reg);
    QVector<RegistrationStruct> getRegistrations();

    void registerAll();

signals:
    //void Register(QString aor, QString registrar, QString proxy, QString auth, QString password, QString lpn, QString user_agent);
    //void Unregister(QString aor, QString registrar, QString proxy, QString auth, QString password, QString lpn, QString user_agent);

    void Register(RegistrationStruct r);
    void Unregister(RegistrationStruct r);
public slots:
    void RegistrationSuccess(QString aor, QString registrar);
    void RegistrationError(QString aor, QString registrar);

};

#endif // REGISTRATIONSMODEL_H
