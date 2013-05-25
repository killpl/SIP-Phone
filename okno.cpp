#include "okno.h"
#include "ui_okno.h"


Okno::Okno(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Okno)
{
    ui->setupUi(this);

    manager = new phoneManager();
}

Okno::~Okno()
{
    delete ui;
    delete manager;
}

void Okno::on_pushButton_Call_clicked()
{

}

void Okno::on_pushButton_Hangup_clicked()
{

}

void Okno::on_pushButton_1_clicked()
{
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"1");
}

void Okno::on_pushButton_2_clicked()
{
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"2");
}

void Okno::on_pushButton_3_clicked()
{
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"3");
}

void Okno::on_pushButton_4_clicked()
{
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"4");
}

void Okno::on_pushButton_5_clicked()
{
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"5");
}

void Okno::on_pushButton_6_clicked()
{
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"6");
}

void Okno::on_pushButton_7_clicked()
{
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"7");
}

void Okno::on_pushButton_8_clicked()
{
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"8");
}

void Okno::on_pushButton_9_clicked()
{
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"9");
}

void Okno::on_pushButton_0_clicked()
{
    ui->lineEditNumber->setText(ui->lineEditNumber->text()+"0");
}

void Okno::on_pushButton_Backspace_clicked()
{
    QString m = ui->lineEditNumber->text();
    m.chop(1);
     ui->lineEditNumber->setText(m);
}

void Okno::on_pushButton_Clear_clicked()
{
    ui->lineEditNumber->setText("");
}

