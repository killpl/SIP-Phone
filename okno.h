#ifndef OKNO_H
#define OKNO_H

#include <QMainWindow>
#include <QAbstractItemView>
#include <QMessageBox>

#include "phonemanager.h"

#include "contactdelegate.h"

#include "contactsmodel.h"
#include "historymodel.h"

#include "settings.h"
#include "configuration.h"
#include "addcontact.h"

using namespace std;

class phoneManager;
class Settings;

namespace Ui {
class Okno;
}

class Okno : public QMainWindow
{
    Q_OBJECT

    phoneManager* manager;

    Settings* settings;
    
    enum StatesUI{
        Idle,
        Incomming,
        Calling,
        InCall,
        OnHold,
        Error // TODO: Future - more errors
    };

    StatesUI currentState;
    void StateChange(StatesUI state);
    string activeCall;

    void setNumberText(QString text);

    ContactsModel* cModel;
    HistoryModel* hModel;

public:
    explicit Okno(QWidget *parent = 0);
    ~Okno();
    
    void onCallsUpdate();
    void onRegistrationsUpdate();
    void onHistoryUpdate();
    void showMessage(QString text);

signals:
    void RegistrationSuccess(QString aor, QString registrar);
    void RegistrationFailed(QString aor, QString registrar);

private slots:
    void RegistrationAdd(RegistrationStruct r);
    void RegistrationRemove(RegistrationStruct r);

    void on_pushButton_Call_clicked();

    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_0_clicked();

    void on_pushButton_Backspace_clicked();
    void on_pushButton_Clear_clicked();
    void on_pushButton_Hangup_clicked();
    void on_pushButtonToggleRight_clicked();
    void on_actionKonfiguracja_programu_2_triggered();
    void on_pushButtonAdd_clicked();
    void on_pushButtonRemove_clicked();

private:
    Ui::Okno *ui;
};

#endif // OKNO_H

