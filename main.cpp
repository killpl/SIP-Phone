#include <QApplication>
#include "okno.h"

#include <ptlib.h>
#include <ptlib/pprocess.h>


class OpalPhone:public PProcess{
    PCLASSINFO(OpalPhone,PProcess);
public:
    void Main(){
        PTrace::SetLevel(2);

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
