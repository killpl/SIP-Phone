#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QtXml>
#include <QMap>
#include <QDebug>

#include <vector>

#include "logger.h"
#include "structs.h"

#include <QVector>


class configuration
{    
    configuration();
    configuration(const logger&);
    configuration& operator=(const logger&);
    ~configuration() { }

    // Mapa wartosci ustawien
    QMap<QString, QVariant> settingsMap;
    QVector<RegistrationStruct> registrations;
    QVector<ContactStruct> contacts;


public:
    static configuration& instance(){
        static configuration instance;
        return instance;
    }

    bool loadConfiguration(string filename);
    bool saveConfiguration(string filename);

    QVector<RegistrationStruct> getRegistrations();
    void setRegistrations(QVector<RegistrationStruct> regs);

    void setAddressbook(QVector<ContactStruct> contacts);
    QVector<ContactStruct> getAdddressbook();

    // Pobieranie konkretnych wartości
    void set(QString name, QVariant value);
    QVariant get(QString name);
};

#endif // CONFIGURATION_H
