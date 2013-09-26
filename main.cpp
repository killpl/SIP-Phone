#include <QApplication>
#include "okno.h"

#include <ptlib.h>
#include <ptlib/pprocess.h>
#include "configuration.h"

class OpalPhone:public PProcess{
    PCLASSINFO(OpalPhone,PProcess);
public:
    void Main(){
        //PTrace::SetLevel(2);

        vector<RegistrationStruct> regs;
        RegistrationStruct r;
        r.aor = "123";
        r.registrar_address = "127.0.0.1";
        regs.push_back(r);
        r.aor = "567";
        regs.push_back(r);

        configuration::instance().setRegistrations(regs);
        configuration::instance().set("test", "test");
        configuration::instance().set("numerek", 123);

        configuration::instance().saveConfiguration("test");


        int argc=1;
        char**argv=new char*[argc];
        for(int i=0;i<argc;i++)
            argv[i]=new char[255];
        argv[0] = argv[1] = 0;

        QApplication a(argc, argv);
        Okno w;
        w.show();

        a.exec();
    }
};

PCREATE_PROCESS(OpalPhone)
