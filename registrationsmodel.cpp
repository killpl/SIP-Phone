#include "RegistrationsModel.h"

RegistrationsModel::RegistrationsModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    registrations = configuration::instance().getRegistrations();
}

void RegistrationsModel::registerAll(){
    foreach(RegistrationStruct r, registrations){
        if(r.aor!="" && r.authID !="" && r.local_party_name !="" && r.password != "" && r.registrar_address != "")
            emit Register(r);
    }
}

int RegistrationsModel::rowCount(const QModelIndex &parent) const
{
    return registrations.size();
}

int RegistrationsModel::columnCount(const QModelIndex &parent) const
{
    return 7;
}

QVariant RegistrationsModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role == Qt::DisplayRole)
     {
         if (orientation == Qt::Horizontal) {
             switch (section)
             {
             case 0:
                 return QString("AOR");
             case 1:
                 return QString("Registrar address");
             case 2:
                 return QString("Proxy address");
             case 3:
                 return QString("Lokalna nazwa");
             case 4:
                 return QString("Auth ID");
             case 5:
                 return QString::fromUtf8("Hasło");
             case 6:
                 return QString("Aktywne");
             }
         }
     }
     return QVariant();
}

QVariant RegistrationsModel::data(const QModelIndex &index, int role) const
{
    if(role==Qt::DisplayRole)
    {
        switch(index.column()){
            case 0:
                return QString(registrations[index.row()].aor.c_str());
            case 1:
                return QString(registrations[index.row()].registrar_address.c_str());
            case 2:
                return QString(registrations[index.row()].proxy_address.c_str());
            case 3:
                return QString(registrations[index.row()].local_party_name.c_str());
            case 4:
                return QString(registrations[index.row()].authID.c_str());
            case 5:
                return QString(registrations[index.row()].password.c_str());
            /*case 7:
                return QVariant(QBool(registrations[index.row()].active));*/
        }
    }

    if(role==Qt::BackgroundRole){
        if(!(
            registrations[index.row()].aor.size()>0 &&
            registrations[index.row()].registrar_address.size()>0 &&
            //registrations[index.row()].proxy_address.size()>0 && // Nieobowiazkowe
            registrations[index.row()].local_party_name.size()>0 &&
            registrations[index.row()].authID.size()>0 &&
            registrations[index.row()].password.size()>0
           ))
        {
            return QColor(255,0,0,70);
        }
    }

    if(role == Qt::DecorationRole){
        if(index.column()==6){
            if(registrations[index.row()].active)
                return QIcon(":/icons/icons/Black_Plus.png");
            else
                return QIcon(":/icons/icons/Black_Remove.png");
        }
    }
    return QVariant();
}

bool RegistrationsModel::setData(const QModelIndex& index, const QVariant& value, int role){
    if(role==Qt::EditRole){
        emit Unregister(registrations[index.row()]);
        switch(index.column()){
            case 0:
                registrations[index.row()].aor = value.toString().toStdString();
                break;

            case 1:
                registrations[index.row()].registrar_address = value.toString().toStdString();
                break;

            case 2:
                registrations[index.row()].proxy_address = value.toString().toStdString();
                break;

            case 3:
                registrations[index.row()].local_party_name = value.toString().toStdString();
                break;

            case 4:
                registrations[index.row()].authID = value.toString().toStdString();
                break;

            case 5:
                registrations[index.row()].password = value.toString().toStdString();
                break;
        }

        if(registrations[index.row()].aor!="" && registrations[index.row()].authID!="" && registrations[index.row()].local_party_name!="" &&
           registrations[index.row()].password!="" && registrations[index.row()].registrar_address!=""){
            emit Register(registrations[index.row()]);
        }/* else {

        }*/
    }
    return true;
}

Qt::ItemFlags RegistrationsModel::flags(const QModelIndex & index) const{
    if(index.column()<7){
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled ;
    } else
        return QAbstractTableModel::flags(index);
}

void RegistrationsModel::addEmpty(){
    addRegistration(RegistrationStruct());
}

void RegistrationsModel::removeRow(QModelIndex& index){
    this->beginRemoveRows(QModelIndex(), index.row(), index.row());
    registrations.remove(index.row());
    this->endRemoveRows();
}

void RegistrationsModel::addRegistration(RegistrationStruct reg){
    this->beginInsertRows(QModelIndex(), registrations.size(), registrations.size());
    registrations.push_back(reg);
    this->endInsertRows();
}


// SLOTS -------------------------------------
void RegistrationsModel::RegistrationSuccess(QString aor, QString registrar){
    for(auto it=registrations.begin(); it!=registrations.end(); it++){
        if(it->aor==aor.toStdString() && it->registrar_address==registrar.toStdString()){
            it->active = true;
            return;
        }
    }
}

void RegistrationsModel::RegistrationError(QString aor, QString registrar){
    for(auto it=registrations.begin(); it!=registrations.end(); it++){
        if(it->aor==aor.toStdString() && it->registrar_address==registrar.toStdString()){
            it->active = false;
            return;
        }
    }
}

QVector<RegistrationStruct> RegistrationsModel::getRegistrations(){
    return registrations;
}
