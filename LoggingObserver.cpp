//
// Created by Sean on 2021-11-12.
//

#include "LoggingObserver.h"

ILoggable::~ILoggable() {}

Observer::Observer() {}

Observer::~Observer() {}

Subject::Subject() {
    _observers = new std::list<Observer *>;
}

Subject::~Subject() {
    delete _observers;
}

void Subject::Attach(Observer *observer) {
    _observers->push_back(observer);
}

void Subject::Detach(Observer *observer) {
    _observers->remove(observer);
}

void Subject::Notify(ILoggable *loggable) {
    std::list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update(loggable);
}

LogObserver::LogObserver() {}

LogObserver::~LogObserver() {}

void LogObserver::Update(ILoggable *loggable) {
    std::string LogFile = "gamelog.txt";
    //std::filesystem::current_path("../Logs");
    std::ofstream output;

    output.open(LogFile, std::ios_base::app);
    std::string log = loggable->stringToLog();

    output << log << std::endl;

    output.close();
}
