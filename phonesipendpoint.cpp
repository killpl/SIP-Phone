#include "phonesipendpoint.h"

phoneSIPEndpoint::phoneSIPEndpoint(OpalManager& manager):SIPEndPoint(manager)
{
}

map<PString, Registration> phoneSIPEndpoint::getRegistrations(){
    return registrations;
}

void phoneSIPEndpoint::OnRegistered(const PString &aor, PBoolean wasRegistering){
    registrations.at(aor).active = true;

    SIPEndPoint::OnRegistered(aor, wasRegistering);
}

bool phoneSIPEndpoint::Register(const PString &host, const PString &user, const PString &autName, const PString &password, const PString &authRealm, unsigned expire =200, const PTimeInterval &minRetryTime =0, const PTimeInterval &maxRetryTime=0){

    Registration r;
    r.aor = string((const char*)user);
    r.authID = (const char*)autName;
    r.password = (const char*)password;
    r.registrar_address = (const char*)host;
    r.user_agent = (const char*)user;

    PString aor = r.aor.c_str();

    registrations.insert(pair<PString, Registration>(aor, r));

    SIPEndPoint::Register(host, user, autName, password, authRealm);

}
