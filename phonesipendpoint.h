#ifndef PHONESIPENDPOINT_H
#define PHONESIPENDPOINT_H

#include <sip/sipep.h>

#include <map>
#include <vector>
#include <string>

#include "structs.h"

using namespace std;

class phoneSIPEndpoint : public SIPEndPoint
{
    map<PString, RegistrationStruct> registrations;

public:
    phoneSIPEndpoint(OpalManager& manager);
    map<PString, RegistrationStruct> getRegistrations();

    virtual void OnRegistered(const PString &aor, PBoolean wasRegistering);
    virtual void OnRegistrationFailed(const PString &aor, SIP_PDU::StatusCodes reason, PBoolean wasRegistering);
    virtual void OnRegistrationStatus(const RegistrationStatus &status);
    virtual bool Register(const PString &host, const PString &proxy, const PString &user, const PString &autName, const PString &password, const PString &authRealm, unsigned expire, const PTimeInterval &minRetryTime, const PTimeInterval &maxRetryTime);
    virtual bool Unregister(const PString &aor);
};

#endif // PHONESIPENDPOINT_H
