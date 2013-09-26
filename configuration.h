#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QtXml>
#include <QMap>

#include <vector>

#include "logger.h"
#include "structs.h"

class configuration
{    
    configuration();
    configuration(const logger&);
    configuration& operator=(const logger&);
    ~configuration() { }

    // Mapa wartosci ustawien
    QMap<QString, QVariant> settingsMap;
    vector<RegistrationStruct> registrations;


public:
    static configuration& instance(){
        static configuration instance;
        return instance;
    }


    bool loadConfiguration(string filename);
    bool saveConfiguration(string filename);

    vector<RegistrationStruct> getRegistrations();
    void setRegistrations(vector<RegistrationStruct> regs);

    // Pobieranie konkretnych wartości
    void set(QString name, QVariant value);
    QVariant get(QString name);

};

#endif // CONFIGURATION_H
