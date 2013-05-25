#ifndef OKNO_H
#define OKNO_H

#include <QMainWindow>
#include "phonemanager.h"

namespace Ui {
class Okno;
}

class Okno : public QMainWindow
{
    Q_OBJECT

    phoneManager* manager;
    
public:
    explicit Okno(QWidget *parent = 0);
    ~Okno();
    
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

private:
    Ui::Okno *ui;
};

#endif // OKNO_H
