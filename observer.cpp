#include "observer.h"

void Observer::setListener(Okno * ok){
    o = ok;
}

RegistrationObserver::RegistrationObserver(Okno* ok){
    connect(this, SIGNAL(notifySignal()), ok, SLOT(onRegistrationsUpdate()));
}

CallsObserver::CallsObserver(Okno* ok){
    connect(this, SIGNAL(notifySignal()), ok, SLOT(onCallsUpdate()));
}

HistoryObserver::HistoryObserver(Okno* ok){
    connect(this, SIGNAL(notifySignal()), ok, SLOT(onHistoryUpdate()));
}


void RegistrationObserver::notify(){
    //o->onRegistrationsUpdate();
    emit notifySignal();
}

void CallsObserver::notify(){
    //o->onCallsUpdate();
    emit notifySignal();
}

void HistoryObserver::notify(){
    //o->onHistoryUpdate();
    emit notifySignal();
}

