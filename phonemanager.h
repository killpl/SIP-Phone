#ifndef PHONEMANAGER_H
#define PHONEMANAGER_H

#include <ptlib.h>
#include <opal.h>
#include <opal/manager.h>
#include <ptlib/sound.h>

#include "phonesipendpoint.h"
#include "phonepcssendpoint.h"

#include "observer.h"
#include "logger.h"
#include "structs.h"
#include "settings.h"

#include <map>

class Observer;


class phoneManager: public OpalManager
{
    friend class phoneSIPEndpoint;
    friend class Settings;

private:
    vector<Observer*> callObservers;
    vector<Observer*> regObservers;
    vector<Observer*> histObservers;

    string defaultServer;
    OpalListenerUDP *listener;

    // Endpoints
    phoneSIPEndpoint* sipEP = NULL;
    phonePCSSEndpoint* pcssEP = NULL;

    map<string, CallStruct*> calls;
    vector<HistoryStruct> history;

    void notifyCallChange();
    void notifyRegChange();
    void notifyHistChange();

public:
    phoneManager();
    ~phoneManager();

    string  Call(string number);
    string Call(string register, string number);
    bool Answer(string token);
    bool Hangup(string token);
    bool Reject(string token);
    bool Transfer(string token, string destination);
    bool Hold(string token);

    // Rozmowy
    vector<CallStruct*> getIncommingCalls();
    vector<CallStruct*> getOutgoinCalls();
    vector<CallStruct*> getActiveCalls();
    vector<HistoryStruct> getCallsHistory();

    // Rejestracja do serwera
    bool Register(string host,string proxy, string user, string auth, string password, string realm);
    bool Register(RegistrationStruct r);
    bool Unregister(RegistrationStruct r);
    map<PString, RegistrationStruct> getRegistrations();
    void registerCallsObserver(Observer*);
    void registerRegsObserver(Observer*);
    void registerHistObserver(Observer*);
    void unregisterAll();

    void setSIPPort(int port);

    CallStruct* getCall(string token);

private:
    // Callbacks
    void OnAlerting(OpalConnection &connection);
    OpalConnection::AnswerCallResponse OnAnswerCall(OpalConnection &connection, const PString &caller);
    void OnClearedCall(OpalCall &call);
    void OnHold(OpalConnection &connection, bool fromRemote, bool onHold);
    void OnEstablishedCall(OpalCall &call);
    PBoolean OnIncomingConnection(OpalConnection &connection, unsigned options, OpalConnection::StringOptions *stringOptions);
};

#endif // PHONEMANAGER_H
