#ifndef PHONEMANAGER_H
#define PHONEMANAGER_H

#include <ptlib.h>
#include <opal.h>
#include <opal/manager.h>
#include <ptlib/sound.h>

#include "phonesipendpoint.h"
#include "phonepcssendpoint.h"

#include "observer.h"

#include <map>

class Observer;

class CallStruct{
public:
    string token;   // token

    bool active;    // answered
    bool hold;      // on hold
    bool incoming;  // in or out

    string partyA;  // source
    string partyB;  // dest

    string begin;   // call begin time
};

class phoneManager: public OpalManager
{
private:
    vector<Observer*> callObservers;
    vector<Observer*> regObservers;

    string defaultServer;

    // Endpoints
    phoneSIPEndpoint* sipEP;
    phonePCSSEndpoint* pcssEP;

    map<string, CallStruct*> calls;

    void notifyCallChange();
    void notifyRegChange();

public:
    phoneManager();

    string  Call(string number);
    bool Call(string register, string number);
    bool Answer(string token);
    bool Hangup(string token);
    bool Reject(string token);
    bool Transfer(string token, string destination);
    bool Hold(string token);

    // Rozmowy
    vector<CallStruct*> getIncommingCalls();
    vector<CallStruct*> getOutgoinCalls();
    vector<CallStruct*> getActiveCalls();

    // Rejestracja do serwera
    bool Register(string host, string user, string auth, string password, string realm);
    bool Unregister(Registration r);

    void registerCallsObserver(Observer*);
    void registerRegsObserver(Observer*);

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
