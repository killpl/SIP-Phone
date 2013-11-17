#include "addcontact.h"
#include "ui_addcontact.h"

AddContact::AddContact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddContact)
{
    ui->setupUi(this);
}

AddContact::~AddContact()
{
    delete ui;
}
