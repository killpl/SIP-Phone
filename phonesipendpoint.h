#ifndef PHONESIPENDPOINT_H
#define PHONESIPENDPOINT_H

#include <sip/sipep.h>

#include <map>
#include <vector>
#include <string>

using namespace std;

class Registration{
public:
    string aor;
    string user_agent;
    string registrar_address;
    string local_party_name;
    string password;
    string authID;
    string token;

    bool active;
};

class phoneSIPEndpoint : public SIPEndPoint
{
    map<PString, Registration> registrations;

public:
    phoneSIPEndpoint(OpalManager& manager);
    map<PString, Registration> getRegistrations();

    virtual void OnRegistered(const PString &aor, PBoolean wasRegistering);
    virtual bool Register(const PString &host, const PString &user, const PString &autName, const PString &password, const PString &authRealm, unsigned expire, const PTimeInterval &minRetryTime, const PTimeInterval &maxRetryTime);
};

#endif // PHONESIPENDPOINT_H
