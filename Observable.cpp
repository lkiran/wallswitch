#include "Observable.h"

bool Observer::operator==(const Observer &rhs) const
{
    if (*this == rhs)
        return true;

    return false;
}

void Subject::Attach(Observer &o)
{
    observers.push_back(&o);
}

void Subject::Detach(Observer &o)
{
}

void Subject::Notify()
{
    for (auto *o : observers)
    {
        o->Update(*this);
    }
}
