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

// Iloggable Interface
class ILoggable {
public:
    ~ILoggable();
    virtual std::string stringToLog() = 0;

    ILoggable& operator =(const ILoggable & o1);
    friend std::ostream & operator << (std::ostream &out, const ILoggable &logObserver);
};

// Observer Interface
class Observer {
public:
    ~Observer();
    virtual void Update(ILoggable *loggable) = 0;

    Observer& operator =(const Observer & o1);
    Observer(const Observer &o1);
    friend std::ostream & operator << (std::ostream &out, const Observer &logObserver);

protected:
    Observer();
};

// Subject Interface
class Subject {
public:
    virtual void Attach(Observer *observer);
    virtual void Detach(Observer *observer);
    virtual void Notify(ILoggable *loggable);
    Subject();
    ~Subject();

    Subject& operator =(const Subject & s1);
    Subject(const Subject &s1);
    friend std::ostream & operator << (std::ostream &out, const Subject &subject);

protected:
    std::list<Observer *> *_observers;
};

// LogObserver (Observer for the project, Logs to the logfile)
class LogObserver : public Observer {
public:
    LogObserver();
    ~LogObserver();
    void Update(ILoggable *loggable) override;

    LogObserver& operator =(const LogObserver & o1);
    LogObserver(const LogObserver &o1);
    friend std::ostream & operator << (std::ostream &out, const LogObserver &logObserver);

private:
};

#endif//CMAKELISTS_TXT_LOGGINGOBSERVER_H
