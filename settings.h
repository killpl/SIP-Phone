#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QHeaderView>

#include "settings.h"
#include "registrationsmodel.h"


namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

    RegistrationsModel* model;
    
public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    void registerAll();
    
signals:
    void Register(RegistrationStruct r);
    void Unregister(RegistrationStruct r);

    void RegistrationSuccess(QString aor, QString registrar);
    void RegistrationFailed(QString aor, QString registrar);

private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonAddRegistration_clicked();

    void on_pushButtonRemoveRegistration_clicked();

    void onClose();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
