#include "okno.h"
#include "ui_okno.h"


Okno::Okno(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Okno)
{
    ui->setupUi(this);

    // Startowe ustawienia okna
    ui->widgetRight->hide();
    setFixedWidth(260);
    setWindowTitle("Softphone");

    activeCall = "";

    manager = new phoneManager();

    Observer* ob = new CallsObserver();
    ob->setListener(this);
    manager->registerCallsObserver(ob);

    ob = new RegistrationObserver();
    ob->setListener(this);
    manager->registerRegsObserver(ob);




    ui->listViewAddressbook->setModel(new contactsModel(this));
    ui->listViewAddressbook->setDragEnabled(true);
    ui->listViewAddressbook->setItemDelegate(new ContactDelegate(this));
    ui->listViewAddressbook->setDragEnabled(true);
    ui->listViewAddressbook->setAcceptDrops(false);
    ui->listViewAddressbook->setDragDropMode(QAbstractItemView::DragOnly);

    StateChange(Idle);

}

Okno::~Okno()
{
    delete ui;
    delete manager;
}

void Okno::StateChange(StatesUI state){
    currentState = state;

    switch(state){

    case Idle:
        ui->lineEditNumber->setDisabled(false);
        ui->pushButton_Call->setEnabled(true);
        ui->pushButton_Hangup->setEnabled(false);
        ui->lineEditNumber->setText("");
        break;

    case Incomming:
    case Calling:
        ui->lineEditNumber->setDisabled(true);
        ui->pushButton_Call->setEnabled(true);
        ui->pushButton_Hangup->setEnabled(true);
        break;

    case OnHold:
        ui->lineEditNumber->setDisabled(false);
        ui->pushButton_Call->setEnabled(true);
        ui->pushButton_Hangup->setEnabled(false);
        break;

    case InCall:
        ui->lineEditNumber->setDisabled(true);
        ui->pushButton_Call->setEnabled(false);
        ui->pushButton_Hangup->setEnabled(false);
        ui->pushButton_Hangup->setEnabled(true);
        break;

    }
}

void Okno::on_pushButton_Call_clicked()
{
    if(currentState==Idle){
        //activeCall = manager->Call("sip:" + ui->lineEditNumber->text().toStdString()+"@192.168.2.1");
        activeCall = manager->Call(ui->comboBoxCallingNumber->currentText().toStdString(),"sip:" + ui->lineEditNumber->text().toStdString()+"@192.168.2.1");
        if(activeCall!="")
            StateChange(Calling);
        else
        {
            // TODO: Error message
            StateChange(Idle);
        }
    }
    if(currentState==Incomming)
        manager->Answer(activeCall);
}

void Okno::on_pushButton_Hangup_clicked()
{
    cout << "Hangup" << endl;

    if(activeCall!=""){
        manager->Hangup(activeCall);
        activeCall = "";
    } else {
        cout << "Warning, no call to hangup" << endl;
    }
    StateChange(Idle);
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


void Okno::on_pushButtonToggleRight_clicked()
{
    if(ui->widgetRight->isHidden()){
        ui->widgetRight->show();
        ui->pushButtonToggleRight->setText("<");
        setFixedWidth(700);
    } else {
        ui->widgetRight->hide();
        ui->pushButtonToggleRight->setText(">");
        setFixedWidth(260);
    }
}


void Okno::setNumberText(QString text){
    if(text.contains("sip:")){
        text = text.mid(4,text.indexOf("@")-4);
    }
    ui->lineEditNumber->setText(text);
}

void Okno::onCallsUpdate(){
    cout << "Calls update" << endl;

    vector<CallStruct*> vIn = manager->getIncommingCalls();
    vector<CallStruct*> vOut = manager->getOutgoinCalls();

    if(vIn.size()>0){
        CallStruct* c = *vIn.begin();
        activeCall = c->token;
        setNumberText(c->partyB.c_str());
        //ui->lineEditNumber->setText(c->partyB.c_str());

        if(c->active)
            StateChange(InCall);
        else
            StateChange(Incomming);
    }


    if(vOut.size()==0 && vIn.size()==0){
        StateChange(Idle);
        activeCall = "";
        ui->lineEditNumber->setText("");

    }

    // Backup
    if(activeCall=="" && manager->getActiveCalls().size()>0){
        activeCall = (*manager->getActiveCalls().begin())->token;
        StateChange(InCall);
    }
}

void Okno::onRegistrationsUpdate(){
    map<PString, RegistrationStruct> regs = manager->getRegistrations();

    ui->comboBoxCallingNumber->clear();
    for(map<PString, RegistrationStruct>::iterator it = regs.begin(); it!=regs.end(); it++){
        ui->comboBoxCallingNumber->addItem((*it).second.aor.c_str());
    }
    ui->comboBoxCallingNumber->setCurrentIndex(0);
}

void Okno::on_actionKonfiguracja_programu_2_triggered()
{
    (new Settings(NULL))->show();
}
