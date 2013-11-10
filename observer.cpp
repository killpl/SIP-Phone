#include "observer.h"

void Observer::setListener(Okno * ok){
    o = ok;
}

void RegistrationObserver::notify(){
    o->onRegistrationsUpdate();
}

void CallsObserver::notify(){
    o->onCallsUpdate();
}
