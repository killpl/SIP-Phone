#include "phonemanager.h"
#include "phonemanager.h"


phoneManager::phoneManager():OpalManager()
{
    // Utworzenie endpointow
    sipEP = new phoneSIPEndpoint(*this);
    pcssEP = new phonePCSSEndpoint(*this);

    AddRouteEntry("pc:.* = sip:<da>");
    AddRouteEntry("sip:.* = pc:");

    SetAudioJitterDelay(50,100);

    // Domyslne urzadzenia dzwiekowe
    pcssEP->SetSoundChannelRecordDevice(PSoundChannel::GetDefaultDevice(PSoundChannel::Recorder));
    pcssEP->SetSoundChannelPlayDevice(PSoundChannel::GetDefaultDevice(PSoundChannel::Player));

    // Domyslny sposob obslugi rozmow przychodzacych
    pcssEP->SetDeferredAlerting(false);
    pcssEP->SetDeferredAnswer(true);

    // Utworzenie portu nasluchujacego sip (5060)
    PIPSocket::Address addr = INADDR_ANY;
    OpalListenerUDP *listener = new OpalListenerUDP(*sipEP, addr, 5065);
    sipEP->StartListener(listener);

    // Wylaczenie video
    SetAutoStartReceiveVideo(false);
    SetAutoStartTransmitVideo(false);

    //sipEP->Register(PString("sip.actio.pl"), PString("48858743092"),PString("48858743092"), PString(), PString(), 0);
    sipEP->Register(PString("192.168.2.1"), PString("sip:101@192.168.2.1"),PString("101"), PString("secret101"), PString("asterisk"), 3600, PTimeInterval(), PTimeInterval());
    sipEP->Register(PString("sip.actio.pl"), PString("48858743092"), PString("48858743092") ,PString("haslovoiptrx"),PString(""), 3600, PTimeInterval(), PTimeInterval() );
}

// Zadzwon z pierwszego dostepnego numeru na podany numer
string phoneManager::Call(string number){
    if(sipEP->getRegistrations().size()>0){
        map<PString,Registration>::iterator it;
        for(it = sipEP->getRegistrations().begin(); it!=sipEP->getRegistrations().end(); it++){

            if((*it).second.active==true){
                string t = (*it).first;
                OpalCall* call = this->SetUpCall(PString(number.c_str()), PString(t));
                if(call!=NULL){
                    string token = call->GetToken();

                    CallStruct* s = new CallStruct();
                    s->token = token;
                    s->active = false;
                    s->hold = false;
                    s->incoming = false;
                    s->partyA = t;
                    s->partyB = number;

                    calls.insert(pair<string, CallStruct*>(token, s));
                    return token;
                }
            }
        }
    }
    return "";
}

// Zadzwon z wybranego zarejestrowanego numeru na podany numer
string phoneManager::Call(string registration, string number){

    if(sipEP->getRegistrations().find(registration)!=sipEP->getRegistrations().end()){
        Registration r = sipEP->getRegistrations().at(registration);

        OpalCall* call = this->SetUpCall(PString(number.c_str()),registration);
        if(call!=NULL){
            string token = call->GetToken();

            CallStruct* s = new CallStruct();
            s->token = token;
            s->active = false;
            s->hold = false;
            s->incoming = false;
            s->partyA = registration;
            s->partyB = "sip:"+number+r.registrar_address;

            calls.insert(pair<string, CallStruct*>(token, s));
            return token;
        }
    }
    return "";
}

// Odbierz polaczenie przychodzace
bool phoneManager::Answer(string token){
    return pcssEP->AcceptIncomingCall(token.c_str());
}

// Zakoncz polaczenie
bool phoneManager::Hangup(string token){
    //OpalCall * call = FindCallWithLock(token.c_str());
    return ClearCall(token.c_str());
}

// Odrzuc przychodzace polaczenie
bool phoneManager::Reject(string token){
    return pcssEP->RejectIncomingCall(token.c_str());
}

bool phoneManager::Transfer(string /*token*/, string /*destination*/){
    // TODO:
    return false;
}

bool phoneManager::Hold(string token){
    OpalCall * call = FindCallWithLock(token.c_str());
    if(call!=NULL){
        if(call->IsOnHold())
            call->Retrieve();
        else
            call->Hold();
        return true;
    }
    return false;
}


// Server registration
bool phoneManager::Register(string host, string user, string auth, string password, string realm){

    return sipEP->Register(PString(host.c_str()), PString(user.c_str()), PString(auth.c_str()), PString(password.c_str()), PString(realm.c_str()),0,PTimeInterval(), PTimeInterval());

}

bool phoneManager::Unregister(Registration r){
    return sipEP->Unregister(r.aor);
}

map<PString, Registration> phoneManager::getRegistrations(){
    return sipEP->getRegistrations();
}


// Callbacks
void phoneManager::OnAlerting(OpalConnection &connection){
    OpalManager::OnAlerting(connection);
}

OpalConnection::AnswerCallResponse phoneManager::OnAnswerCall(OpalConnection &connection, const PString &caller){
    string token = connection.GetCall().GetToken();

    logger::instance().log(4, "onAnswerCall " + token);
/*
    if(calls.find(token)!=calls.end()){
        calls.at(token)->active = true;
    } else {
        cout << "Warning [onEstablished], call not found" << endl;
    }
    notifyCallChange();
*/
    return OpalManager::OnAnswerCall(connection, caller);
}

void phoneManager::OnClearedCall(OpalCall &call){
    string token = call.GetToken();

    logger::instance().log(4, "onClearedCall " + token);

    if(calls.find(token)!=calls.end()){
        calls.erase(calls.find(token));
    } else {
        logger::instance().log(4, "Warning [clearedCal], call not found");
    }

    notifyCallChange();
    OpalManager::OnClearedCall(call);
}

void phoneManager::OnHold(OpalConnection &connection, bool fromRemote, bool onHold){
     string token = connection.GetCall().GetToken();

     logger::instance().log(4, "onHold " + token);

     if(calls.find(token)!=calls.end()){
         calls.at(token)->hold = onHold;
     } else {
          logger::instance().log(4,"Warning [onHold], call not found");
     }

     notifyCallChange();
     OpalManager::OnHold(connection, fromRemote, onHold);
}

void phoneManager::OnEstablishedCall(OpalCall &call){
    string token = call.GetToken();

    logger::instance().log(4, "onEstablishedCall "+ token);

    if(calls.find(token)!=calls.end()){
        calls.at(token)->active = true;
    } else {
        logger::instance().log(4,"Warning [onEstablished], call not found");
    }

    cout << "Established" << endl;

    notifyCallChange();
    OpalManager::OnEstablishedCall(call);
}

PBoolean phoneManager::OnIncomingConnection(OpalConnection &conn, unsigned options, OpalConnection::StringOptions *stringOptions){
    string token = conn.GetCall().GetToken();

    logger::instance().log(4, "onIncommingConnection " + token);

    if(calls.find(token)!=calls.end()){
        logger::instance().log(4,"Warning [onIncommingConnection], token repeat");
    } else {
        CallStruct* s = new CallStruct();
        s->token = token;
        s->active = false;
        s->hold = false;
        s->incoming = true;
        string pb = conn.GetCall().GetPartyA(), pa = conn.GetCall().GetRemoteParty();
        s->partyA = pa;
        s->partyB = pb;
        //cout << pa << "]\n[" << pb << endl;

        calls.insert(pair<string, CallStruct*>(token, s));
    }

    notifyCallChange();
    return OpalManager::OnIncomingConnection(conn, options, stringOptions);
}

// Other
void phoneManager::registerCallsObserver(Observer* o){
    callObservers.push_back(o);
}

void phoneManager::registerRegsObserver(Observer* o){
    regObservers.push_back(o);
}

void phoneManager::notifyCallChange(){
    vector<Observer*>::iterator it;
    for(it=callObservers.begin(); it!=callObservers.end(); it++){
        (*it)->notify();
    }
}

void phoneManager::notifyRegChange(){
    vector<Observer*>::iterator it;
    for(it=regObservers.begin(); it!=regObservers.end(); it++){
        (*it)->notify();
    }
}

CallStruct* phoneManager::getCall(string token){
    if(calls.find(token)!=calls.end())
        return calls.at(token);
    else
        return NULL;
}

vector<CallStruct*> phoneManager::getIncommingCalls(){
    vector<CallStruct*> v;
    for(map<string, CallStruct*>::iterator it = calls.begin(); it!=calls.end(); it++){
        if((*it).second->incoming)
            v.push_back((*it).second);
    }
    return v;
}

vector<CallStruct*> phoneManager::getOutgoinCalls(){
    vector<CallStruct*> v;
    for(map<string, CallStruct*>::iterator it = calls.begin(); it!=calls.end(); it++){
        if(!(*it).second->incoming)
            v.push_back((*it).second);
    }
    return v;
}

vector<CallStruct*> phoneManager::getActiveCalls(){
    vector<CallStruct*> v;
    for(map<string, CallStruct*>::iterator it = calls.begin(); it!=calls.end(); it++){
        if((*it).second->active)
            v.push_back((*it).second);
    }
    return v;
}
