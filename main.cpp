#include <QApplication>
#include <QStyleFactory>

#include "okno.h"

#include <ptlib.h>
#include <ptlib/pprocess.h>
#include "configuration.h"

class OpalPhone:public PProcess{
    PCLASSINFO(OpalPhone,PProcess);
public:
    void Main(){
        //PTrace::SetLevel(3);

        int argc=1;
        char**argv=new char*[argc];
        for(int i=0;i<argc;i++)
            argv[i]=new char[255];
        argv[0] = argv[1] = 0;

        QApplication a(argc, argv);

        QFile File(":/style/style.qss");
        File.open(QFile::ReadOnly);
        QString ss = QString::fromUtf8(File.readAll());
        a.setStyleSheet(ss);

        a.setStyle(QStyleFactory::create("gtk"));

        Okno w;
        w.show();

        a.exec();
    }
};

PCREATE_PROCESS(OpalPhone)
