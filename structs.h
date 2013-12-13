#ifndef STRUCTS_H
#define STRUCTS_H

#include <Qt>
#include <string>
using namespace std;

// SIP Registration

struct RegistrationStruct{
    string aor;
    //string user_agent;
    string registrar_address;
    string proxy_address; // If differet than registrar
    string local_party_name;
    string password;
    string authID;
    string token;

    bool active;
};

// SIP Call
struct CallStruct{
    string token;   // token

    bool active;    // answered
    bool hold;      // on hold
    bool incoming;  // in or out

    string partyA;  // source
    string partyB;  // dest

    string begin;   // call begin time
};

// Contact entry
struct ContactStruct{
    string name;
    string email;
    string number;
};

struct HistoryStruct{
    string number;
    string reason;
    int type;
    // 0 - incomming
    // 1 - outgoing
    // 2 - not answered
};





#endif // STRUCTS_H
