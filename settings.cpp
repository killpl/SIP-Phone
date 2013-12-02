#include "settings.h"
#include "ui_settings.h"

Settings::Settings(phoneManager *m, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    this->manager = m;

    model = new RegistrationsModel(ui->tableViewRegistrations);
    ui->tableViewRegistrations->setModel(model);
    ui->tableViewRegistrations->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

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

void Settings::saveSettings(){
    configuration::instance().set("UDPPortsMin", ui->lineEditMinUDP->text());
    configuration::instance().set("UDPPortsMax", ui->lineEditMaxUDP->text());
    configuration::instance().set("RTPPortsMin", ui->lineEditMinRTP->text());
    configuration::instance().set("RTPPortsMax", ui->lineEditMaxRTP->text());
    configuration::instance().set("JitterMin", ui->lineEditMinJitter->text());
    configuration::instance().set("JitterMax", ui->lineEditMaxJitter->text());
    configuration::instance().set("NoMediaTimeout", ui->lineEditNoMediaTimeout->text());
    configuration::instance().set("EchoCanceler", ui->checkBoxEchoCancel->checkState());

    configuration::instance().set("RetryMin", ui->lineEditMinRetry->text());
    configuration::instance().set("RetryMax", ui->lineEditMaxRetry->text());
    configuration::instance().set("InviteMin", ui->lineEditMinTimeout->text());
    configuration::instance().set("InviteMax", ui->lineEditMaxTimeout->text());
    configuration::instance().set("ACKMin", ui->lineEditMinACK->text());
    configuration::instance().set("ACKMax", ui->lineEditMaxACK->text());
    configuration::instance().set("RegistrarMin", ui->lineEditMinTTL->text());
    configuration::instance().set("RegistrarMax", ui->lineEditMaxTTL->text());

    configuration::instance().set("SIPPort", ui->lineEditPortSIP->text());
    configuration::instance().set("UserAgent", ui->lineEditUserAgent->text());
}

void Settings::loadSettings(){

    int min = configuration::instance().get("UDPPortsMin").toInt();
    int max = configuration::instance().get("UDPPortsMax").toInt();
    this->setUDP(min, max);
    ui->lineEditMinUDP->setText(QString::number(min));
    ui->lineEditMaxUDP->setText(QString::number(max));

    min = configuration::instance().get("RTPPortsMin").toInt();
    max = configuration::instance().get("RTPPortsMax").toInt();
    this->setRTP(min, max);
    ui->lineEditMinRTP->setText(QString::number(min));
    ui->lineEditMaxRTP->setText(QString::number(max));

    min = configuration::instance().get("JitterMin").toInt();
    max = configuration::instance().get("JitterMax").toInt();
    this->setJitter(min, max);
    ui->lineEditMinJitter->setText(QString::number(min));
    ui->lineEditMaxJitter->setText(QString::number(max));

    min = configuration::instance().get("NoMediaTimeout").toInt();
    this->setNoMediaTimeout(min);
    ui->lineEditNoMediaTimeout->setText(QString::number(min));

    bool state = configuration::instance().get("EchoCanceler").toBool();
    this->setEchoCanceler(state);
    if(state)
        ui->checkBoxEchoCancel->setChecked(true);
    else
        ui->checkBoxEchoCancel->setChecked(false);

    min = configuration::instance().get("RetryMin").toInt();
    max = configuration::instance().get("RetryMax").toInt();
    this->setRetryTimeout(min, max);
    ui->lineEditMinRetry->setText(QString::number(min));
    ui->lineEditMaxRetry->setText(QString::number(max));

    min = configuration::instance().get("InviteMin").toInt();
    max = configuration::instance().get("InviteMax").toInt();
    this->setInviteTimeout(min, max);
    ui->lineEditMinTimeout->setText(QString::number(min));
    ui->lineEditMaxTimeout->setText(QString::number(max));

    min = configuration::instance().get("ACKMin").toInt();
    max = configuration::instance().get("ACKMax").toInt();
    this->setACKTimeout(min, max);
    ui->lineEditMinACK->setText(QString::number(min));
    ui->lineEditMaxACK->setText(QString::number(max));

    min = configuration::instance().get("RegistrarMin").toInt();
    max = configuration::instance().get("RegistrarMax").toInt();
    this->setRegistrarTTL(min, max);
    ui->lineEditMinTTL->setText(QString::number(min));
    ui->lineEditMaxTTL->setText(QString::number(max));


    if(configuration::instance().get("SIPPort").toString()!=ui->lineEditPortSIP->text()){
        min = configuration::instance().get("SIPPort").toInt();
        this->setSIPPort(min);
        ui->lineEditPortSIP->setText(QString::number(min));
    }

    QString ua = configuration::instance().get("UserAgent").toString();
    this->setUserAgent(ua.toStdString());
    ui->lineEditUserAgent->setText(ua);
}

void Settings::registerAll(){
    model->registerAll();
}

void Settings::on_pushButtonSave_clicked()
{
    saveSettings();
    this->close();
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

void Settings::setRTP(int min, int max){
    manager->SetRtpIpPorts(min, max);
}

void Settings::setUDP(int min, int max){
    manager->SetUDPPorts(min, max);
}

void Settings::setJitter(int min, int max){
    manager->SetAudioJitterDelay(min, max);
}

void Settings::setNoMediaTimeout(int min){
    manager->SetNoMediaTimeout(PTimeInterval(min, min));
}

void Settings::setEchoCanceler(bool state){
    OpalEchoCanceler::Params params;
    if(state)
        params.m_mode = OpalEchoCanceler::Cancelation;
    else
        params.m_mode = OpalEchoCanceler::NoCancelation;
    manager->SetEchoCancelParams(params);
}

void Settings::setRetryTimeout(int min, int max){
    manager->sipEP->SetRetryTimeouts(min, max);
}

void Settings::setInviteTimeout(int min, int max){
    manager->sipEP->SetInviteTimeout(PTimeInterval(min,max));
}

void Settings::setACKTimeout(int min, int max){
    manager->sipEP->SetAckTimeout(PTimeInterval(min, max));
}

void Settings::setRegistrarTTL(int min, int max){
    manager->sipEP->SetRegistrarTimeToLive(PTimeInterval(min, max));
}

void Settings::setSIPPort(int port){
    manager->setSIPPort(port);
}


void Settings::setUserAgent(string ua){
    manager->sipEP->SetUserAgent(ua.c_str());
}

