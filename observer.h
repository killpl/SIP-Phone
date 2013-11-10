#ifndef OBSERVER_H
#define OBSERVER_H

#include "okno.h"

class Okno;

class Observer
{
protected:
    Okno* o;
public:

    virtual ~Observer(){}
    virtual void notify() = 0;
    void setListener(Okno *);
};

class RegistrationObserver: public Observer{
    virtual void notify();

};

class CallsObserver : public Observer{
    virtual void notify();
};

#endif // OBSERVER_H
