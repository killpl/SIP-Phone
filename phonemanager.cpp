#include "phonemanager.h"

phoneManager::phoneManager():OpalManager()
{
    sipEP = new phoneSIPEndpoint(*this);
    pcssEP = new phonePCSSEndpoint(*this);

    //this->AttachEndPoint(sipEP, "sip");
    //this->AttachEndPoint(pcssEP, "pc");

    AddRouteEntry("pc:.* = sip:<da>");
    AddRouteEntry("sip:.* = pc:");

    SetAudioJitterDelay(50,100);

    pcssEP->SetSoundChannelRecordDevice(PSoundChannel::GetDefaultDevice(PSoundChannel::Recorder));
    pcssEP->SetSoundChannelPlayDevice(PSoundChannel::GetDefaultDevice(PSoundChannel::Player));

    PIPSocket::Address addr = INADDR_ANY;
    OpalListenerUDP *listener = new OpalListenerUDP(*sipEP, addr, 5060);
    sipEP->StartListener(listener);

    SetAutoStartReceiveVideo(false);
    SetAutoStartTransmitVideo(false);

    //sipEP->Register(PString("sip.actio.pl"), PString("48858743092"),PString("48858743092"), PString(), PString(), 0);
    sipEP->Register(PString("192.168.2.1"), PString("sip:101@192.168.2.1"),PString("101"), PString("secret101"), PString("asterisk"), 3600, PTimeInterval(), PTimeInterval());

}


bool phoneManager::Call(string number){
    if(sipEP->getRegistrations().size()>0){
        for(map<PString,Registration>::iterator it = sipEP->getRegistrations().begin(); it!=sipEP->getRegistrations().end(); it++){
            if((*it).second.active==true){
                this->SetUpCall(PString((*it).first),PString(number.c_str()));
            }
        }

        return true;
    }
    else
        return false;
}

bool phoneManager::Answer(string token){
    pcssEP->AcceptIncomingCall(token.c_str());
}

bool phoneManager::Hangup(string token){
    FindCallWithLock(token.c_str());
}

bool phoneManager::Reject(string token){
    pcssEP->RejectIncomingCall(token.c_str());
}

bool phoneManager::Transfer(string token, string destination){

}

bool phoneManager::Hold(string token){

}


// Server registration
bool phoneManager::Register(string host, string user, string auth, string password, string realm){

    sipEP->Register(PString(host.c_str()), PString(user.c_str()), PString(auth.c_str()), PString(password.c_str()), PString(realm.c_str()),0,PTimeInterval(), PTimeInterval());
}

bool phoneManager::Unregister(Registration r){

}


// Callbacks
void phoneManager::OnAlerting(OpalConnection &connection){

}

OpalConnection::AnswerCallResponse phoneManager::OnAnswerCall(OpalConnection &connection, const PString &caller){

}

void phoneManager::OnClearedCall(OpalCall &call){

}

void phoneManager::OnHold(OpalConnection &connection, bool fromRemote, bool onHold){

}

void phoneManager::OnEstablishedCall(OpalCall &call){

}

void phoneManager::OnNewConnection(OpalConnection &connection){

}
