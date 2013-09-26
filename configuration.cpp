#include "configuration.h"

configuration::configuration()
{
}


bool configuration::loadConfiguration(string filename){
    QDomDocument document;

    QFile conf(filename.c_str());
    if (!conf.open(QIODevice::ReadOnly))
        return false;
    if (!document.setContent(&conf)) {
        conf.close();
        return false;
    }
    conf.close();

    QDomElement docElem = document.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            cout << qPrintable(e.tagName()) << endl; // the node really is an element.
        }
        n = n.nextSibling();
    }



    return true;
}

bool configuration::saveConfiguration(string filename){

    QDomDocument doc;
    QDomElement root = doc.createElement("Configuration");
    doc.appendChild(root);

    QDomElement regs = doc.createElement("Registrations");
    root.appendChild(regs);

    for(RegistrationStruct &r : registrations){
        QDomElement reg = doc.createElement("Registration");
        regs.appendChild(reg);

        QDomElement elem = doc.createElement("aor");
        QDomText t = doc.createTextNode(r.aor.c_str());
        elem.appendChild(t);
        reg.appendChild(elem);

        elem = doc.createElement("authID");
        t = doc.createTextNode(r.authID.c_str());
        elem.appendChild(t);
        reg.appendChild(elem);

        elem = doc.createElement("local_party_name");
        t = doc.createTextNode(r.local_party_name.c_str());
        elem.appendChild(t);
        reg.appendChild(elem);

        elem = doc.createElement("password");
        t = doc.createTextNode(r.password.c_str());
        elem.appendChild(t);
        reg.appendChild(elem);

        elem = doc.createElement("proxy_address");
        t = doc.createTextNode(r.proxy_address.c_str());
        elem.appendChild(t);
        reg.appendChild(elem);

        elem = doc.createElement("registrar_address");
        t = doc.createTextNode(r.registrar_address.c_str());
        elem.appendChild(t);
        reg.appendChild(elem);
    }

    QDomElement settings = doc.createElement("Settings");
    root.appendChild(settings);

    for(auto it = settingsMap.begin(); it!=settingsMap.end(); it++){
        QDomElement elem = doc.createElement(it.key());
        QDomText t = doc.createTextNode(it.value().toString());
        elem.appendChild(t);
        settings.appendChild(elem);
    }

    qDebug() << doc.toString();

    QFile file(filename.c_str());

    // TODO check if open
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << doc.toString();
    file.close();
}

vector<RegistrationStruct> configuration::getRegistrations(){
    return registrations;
}

void configuration::setRegistrations(vector<RegistrationStruct> regs){
    registrations = regs;
}

void configuration::set(QString name, QVariant value){
    settingsMap.insert(name, value);
}

QVariant configuration::get(QString name){
    //return settingsMap.find(name);
}
