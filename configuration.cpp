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
        QDomElement e = n.toElement();
        if(!e.isNull()) {
            if(e.tagName()=="Registrations"){
                QDomNode nodes = n.firstChild();
                while(!nodes.isNull()){
                    if(!nodes.toElement().isNull() && nodes.toElement().tagName()=="Registration"){
                        RegistrationStruct r;
                        QDomNode regNode = nodes.firstChild();
                        while(!regNode.isNull()){
                            QDomElement el = regNode.toElement();
                            if(!el.isNull()){
                                if(el.tagName()=="aor")
                                    r.aor = el.text().toStdString();

                                if(el.tagName()=="authID")
                                    r.authID = el.text().toStdString();

                                if(el.tagName()=="local_party_name")
                                    r.local_party_name = el.text().toStdString();

                                if(el.tagName()=="password")
                                    r.password = el.text().toStdString();

                                if(el.tagName()=="proxy_address")
                                    r.proxy_address = el.text().toStdString();

                                if(el.tagName()=="registrar_address")
                                     r.registrar_address = el.text().toStdString();
                                }
                                regNode = regNode.nextSibling();
                            }
                            r.active = false;
                            registrations.push_back(r);
                        }
                    nodes = nodes.nextSibling();
                    }
            }

            if(e.tagName()=="Settings"){
                QDomNode nodes = n.firstChild();
                while(!nodes.isNull()){
                    QDomElement el = nodes.toElement();
                    if(!el.isNull()){
                        settingsMap.insert(el.tagName(), el.text());
                        nodes = nodes.nextSibling();
                        qDebug() << el.tagName() << el.text();
                    }
                }
            }

            if(e.tagName()=="Addressbook"){
                QDomNode nodes = n.firstChild();
                while(!nodes.isNull()){
                    QDomElement el = nodes.toElement();
                    if(!el.isNull()){
                        ContactStruct c;
                        c.name = el.attribute("Name").toStdString();
                        c.email = el.attribute("Email").toStdString();
                        c.number = el.attribute("Number").toStdString();

                        contacts.push_back(c);

                        nodes = nodes.nextSibling();
                    }
                }
            }
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

    QDomElement addressbook = doc.createElement("Addressbook");
    root.appendChild(addressbook);

    for(auto it = contacts.begin(); it!=contacts.end(); it++){
        QDomElement elem = doc.createElement("Contact");
        elem.setAttribute("Name", it->name.c_str());
        elem.setAttribute("Email", it->email.c_str());
        elem.setAttribute("Number", it->number.c_str());
        addressbook.appendChild(elem);
    }

    QFile file(filename.c_str());
    file.open(QIODevice::WriteOnly);

    if(file.isOpen()){
        QTextStream out(&file);
        out << doc.toString();
        file.close();
    } else {
        logger::instance().log("Configuration file not found");
        return false;
    }

    return true;
}

QVector<RegistrationStruct> configuration::getRegistrations(){
    return registrations;
}

void configuration::setRegistrations(QVector<RegistrationStruct> regs){
    registrations = regs;
}

void configuration::set(QString name, QVariant value){
    settingsMap.insert(name, value);
}

QVariant configuration::get(QString name){
    return settingsMap[name];
}

void configuration::setAddressbook(QVector<ContactStruct> history){
    this->contacts = history;
}

QVector<ContactStruct> configuration::getAdddressbook(){
    return contacts;
}
