
#ifndef Observable_h
#define Observable_h

#include <iostream>
#include <vector>

class Subject; 

class Observer 
{ 
public:
    virtual ~Observer() = default;
    virtual void Update(Subject&) = 0;
    bool operator ==(const Observer &rhs) const;
};

class Subject 
{ 
public: 
     virtual ~Subject() = default;
     void Attach(Observer& o);
     void Detach(Observer& o);
     void Notify();
private:
     std::vector<Observer*> observers; 
};

#endif
