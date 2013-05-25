#ifndef PHONEMANAGER_H
#define PHONEMANAGER_H

#include <ptlib.h>
#include <opal.h>
#include <opal/manager.h>
#include <ptlib/sound.h>

#include "phonesipendpoint.h"
#include "phonepcssendpoint.h"

#include <map>


class Call{
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
    string defaultServer;

    // Endpoints
    phoneSIPEndpoint* sipEP;
    phonePCSSEndpoint* pcssEP;


public:
    phoneManager();

    bool Call(string number);
    bool Answer(string token);
    bool Hangup(string token);
    bool Reject(string token);
    bool Transfer(string token, string destination);
    bool Hold(string token);

    // Server registration
    bool Register(string host, string user, string auth, string password, string realm);
    bool Unregister(Registration r);

private:
    // Callbacks
    void OnAlerting(OpalConnection &connection);
    OpalConnection::AnswerCallResponse OnAnswerCall(OpalConnection &connection, const PString &caller);
    void OnClearedCall(OpalCall &call);
    void OnHold(OpalConnection &connection, bool fromRemote, bool onHold);
    void OnEstablishedCall(OpalCall &call);
    void OnNewConnection(OpalConnection &connection);

};

#endif // PHONEMANAGER_H
