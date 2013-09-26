#include "phonesipendpoint.h"
#include "phonemanager.h"

phoneSIPEndpoint::phoneSIPEndpoint(OpalManager& manager):SIPEndPoint(manager)
{
}

map<PString, RegistrationStruct> phoneSIPEndpoint::getRegistrations(){
    return registrations;
}

void phoneSIPEndpoint::OnRegistered(const PString &aor, PBoolean wasRegistering){
    if(registrations.find(aor)!=registrations.end())
        registrations.at(aor).active = true;
    else
        cout << "Warning [onRegister], registration not found " << aor << endl;

    phoneManager* m = dynamic_cast<phoneManager*>(&(this->GetManager()));
    if(m!=NULL){
        m->notifyRegChange();
    }

    SIPEndPoint::OnRegistered(aor, wasRegistering);
}

void phoneSIPEndpoint::OnRegistrationFailed(const PString &aor, SIP_PDU::StatusCodes reason, PBoolean wasRegistering){
    // TODO

}

void phoneSIPEndpoint::OnRegistrationStatus(const RegistrationStatus &status){
    // TODO

}

bool phoneSIPEndpoint::Register(const PString &host, const PString &user, const PString &autName, const PString &password, const PString &authRealm, unsigned expire =200, const PTimeInterval &minRetryTime =0, const PTimeInterval &maxRetryTime=0){
    RegistrationStruct r;

    string aor2 = user;
    if(aor2.find("sip:") == aor2.npos)
        aor2 = "sip:"+aor2+"@"+(const char*)host;

    r.aor = aor2; //string((const char*)user);
    r.authID = (const char*)autName;
    r.password = (const char*)password;
    r.registrar_address = (const char*)host;
    r.user_agent = (const char*)user;

    PString aor = r.aor.c_str();

    registrations.insert(pair<PString, RegistrationStruct>(aor, r));

    return SIPEndPoint::Register(host, user, autName, password, authRealm);
}
