#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QHeaderView>

#include "settings.h"
#include "registrationsmodel.h"
#include "phonemanager.h"
#include "configuration.h"

#include <opal.h>
#include <opal/manager.h>
#include <ptlib/ptime.h>


namespace Ui {
    class Settings;
}

class phoneManager;

class Settings : public QWidget
{
    Q_OBJECT

    RegistrationsModel* model;
    phoneManager* manager;
    
public:
    explicit Settings(phoneManager* m, QWidget *parent = 0);
    ~Settings();

    void registerAll();
    void saveSettings();
    void loadSettings();
    
signals:
    void Register(RegistrationStruct r);
    void Unregister(RegistrationStruct r);

    void RegistrationSuccess(QString aor, QString registrar);
    void RegistrationFailed(QString aor, QString registrar);

private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonAddRegistration_clicked();
    void on_pushButtonRemoveRegistration_clicked();
    void onClose();

    // Main settings tab
    void setRTP(int min, int max);
    void setUDP(int min, int max);
    void setJitter(int min, int max);
    void setNoMediaTimeout(int min);
    void setEchoCanceler(bool state);

    // SIP settings tab
    void setRetryTimeout(int min, int max);
    void setInviteTimeout(int min, int max);
    void setACKTimeout(int min, int max);
    void setRegistrarTTL(int min, int max);
    void setSIPPort(int port);
    void setUserAgent(string ua);

    /*
    pair<int,int> getRTP();
    pair<int,int> getUDP();
    pair<int,int> getJitter();
    pair<int,int> getNoMediaTimeout();
    */

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
