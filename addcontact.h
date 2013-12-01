#ifndef ADDCONTACT_H
#define ADDCONTACT_H

#include <QDialog>
#include <QAbstractButton>

#include "structs.h"
#include "contactsmodel.h"

namespace Ui {
class AddContact;
}

class AddContact : public QDialog
{
    Q_OBJECT
    
    ContactsModel* model;

public:
    explicit AddContact(ContactsModel* model, QWidget *parent = 0);
    ~AddContact();
    
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::AddContact *ui;
};

#endif // ADDCONTACT_H
