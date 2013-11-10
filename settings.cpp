#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    model = new RegistrationsModel(ui->tableViewRegistrations);
    ui->tableViewRegistrations->setModel(model);
    ui->tableViewRegistrations->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    connect(ui->pushButtonSave, SIGNAL(clicked()), this, SLOT(onClose()));

    connect(model, SIGNAL(Register(RegistrationStruct)), this, SIGNAL(Register(RegistrationStruct)));
    connect(model, SIGNAL(Unregister(RegistrationStruct)), this, SIGNAL(Unregister(RegistrationStruct)));

    connect(this, SIGNAL(RegistrationSuccess(QString,QString)), model, SLOT(RegistrationSuccess(QString,QString)));
    connect(this, SIGNAL(RegistrationFailed(QString,QString)), model, SLOT(RegistrationError(QString,QString)));
}

Settings::~Settings()
{
    delete model;
    delete ui;
}

void Settings::registerAll(){
    model->registerAll();
}

void Settings::on_pushButtonCancel_clicked()
{
    this->close();
}

void Settings::on_pushButtonAddRegistration_clicked()
{
    model->addEmpty();
}

void Settings::on_pushButtonRemoveRegistration_clicked()
{
    foreach(QModelIndex m, ui->tableViewRegistrations->selectionModel()->selectedRows()){
        model->removeRow(m);
    }
}

void Settings::onClose(){
    configuration::instance().setRegistrations(model->getRegistrations());
    configuration::instance().saveConfiguration("test.xml");
    this->close();
}
