#include "addcontact.h"
#include "ui_addcontact.h"

AddContact::AddContact(ContactsModel *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddContact)
{
    ui->setupUi(this);
    this->model = model;
}

AddContact::~AddContact()
{
    delete ui;
}

void AddContact::on_buttonBox_accepted()
{
    ContactStruct contact;
    contact.name = ui->lineEdit->text().toStdString();
    contact.number = ui->lineEdit_2->text().toStdString();
    model->addContact(contact);
}

void AddContact::on_buttonBox_rejected()
{
    this->close();
}
