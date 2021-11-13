//
// Created by Sean on 2021-11-12.
//

#ifndef CMAKELISTS_TXT_LOGGINGOBSERVER_H
#define CMAKELISTS_TXT_LOGGINGOBSERVER_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

class ILoggable {
public:
    virtual ~ILoggable();
    virtual std::string stringToLog();
};

class Observer {
public:
    ~Observer();
    virtual void Update(ILoggable *loggable) = 0;

protected:
    Observer();
};

class Subject {
public:
    virtual void Attach(Observer *observer);
    virtual void Detach(Observer *observer);
    virtual void Notify(ILoggable *loggable);
    Subject();
    ~Subject();

private:
    std::list<Observer *> *_observers;
};

class LogObserver : public Observer {
public:
    LogObserver();
    ~LogObserver();
    void Update(ILoggable *loggable) override;

private:
};

#endif//CMAKELISTS_TXT_LOGGINGOBSERVER_H
