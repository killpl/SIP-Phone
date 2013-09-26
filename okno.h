#ifndef OKNO_H
#define OKNO_H

#include <QMainWindow>
#include <QAbstractItemView>

#include "phonemanager.h"

#include "ContactDelegate.h"
#include "contactsmodel.h"
#include "settings.h"

using namespace std;

class phoneManager;

namespace Ui {
class Okno;
}

class Okno : public QMainWindow
{
    Q_OBJECT

    phoneManager* manager;
    
    enum StatesUI{
        Idle,
        Incomming,
        Calling,
        InCall,
        OnHold,
        Error // TODO: StateChange for error
    };

    StatesUI currentState;
    void StateChange(StatesUI state);
    string activeCall;

    void setNumberText(QString text);

public:
    explicit Okno(QWidget *parent = 0);
    ~Okno();
    
    void onCallsUpdate();
    void onRegistrationsUpdate();



private slots:
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

private:
    Ui::Okno *ui;
};

#endif // OKNO_H
