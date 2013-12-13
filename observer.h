#ifndef OBSERVER_H
#define OBSERVER_H

#include "okno.h"
#include <QObject>

class Okno;

class Observer : public QObject
{
Q_OBJECT

protected:
    Okno* o;
public:

    virtual ~Observer(){}
    virtual void notify() = 0;
    void setListener(Okno *);
};

class RegistrationObserver: public Observer{
Q_OBJECT

public:
    RegistrationObserver(Okno *ok);
    virtual void notify();

signals:
    void notifySignal();
};

class CallsObserver : public Observer{
Q_OBJECT

public:
    CallsObserver(Okno *ok);
    virtual void notify();

signals:
    void notifySignal();
};

class HistoryObserver : public Observer{
Q_OBJECT

public:
    HistoryObserver(Okno *ok);
    virtual void notify();

signals:
    void notifySignal();
};

#endif // OBSERVER_H
