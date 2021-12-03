//
// Created by Sean on 2021-11-12.
//

#include "LoggingObserver.h"

// ILoggable Destructor
ILoggable::~ILoggable() {}

// Assignment Operator
ILoggable &ILoggable::operator=(const ILoggable &s1) {
    return *this;
}

// Stream Output Operator
std::ostream &operator<<(std::ostream &out, const ILoggable &subject) {
    out << "{ILOGGABLE CLASS}";
    return out;
}

// Observer Constructor
Observer::Observer() {}

// Observer Destructor
Observer::~Observer() {}

// Assignment Operator
Observer &Observer::operator=(const Observer &s1) {
    return *this;
}

// Copy Constructor
Observer::Observer(const Observer &s1) {

}

// Stream Output Operator
std::ostream &operator<<(std::ostream &out, const Observer &subject) {
    out << "{OBSERVER CLASS}";
    return out;
}

// Subject Constructor
Subject::Subject() {
    _observers = new std::list<Observer *>;
}

// Subject Destructor
Subject::~Subject() {
    delete _observers;
}

// Method to attach an Observer to a Subject
void Subject::Attach(Observer *observer) {
    _observers->push_back(observer);
}

// Method to remove an Observer to a Subject
void Subject::Detach(Observer *observer) {
    _observers->remove(observer);
}

// Method to notify all Observers of the Subject
void Subject::Notify(ILoggable *loggable) {
    std::list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update(loggable);
}

// Assignment Operator
Subject &Subject::operator=(const Subject &s1) {
    return *this;
}

// Copy Constructor
Subject::Subject(const Subject &s1) {

}

// Stream Output Operator
std::ostream &operator<<(std::ostream &out, const Subject &subject) {
    out << "{SUBJECT CLASS}";
    return out;
}

// LogObserver Constructor
LogObserver::LogObserver() {}

// LogObserver Destructor
LogObserver::~LogObserver() {}

// Method to log the ILoggable's log string
void LogObserver::Update(ILoggable *loggable) {
    // LogFile name
    std::string LogFile = "../gamelog.txt";
    std::ofstream output;

    // Open LogFile and Get LogString
    output.open(LogFile, std::ios_base::app);
    std::string log = loggable->stringToLog();

    // Write LogString to the LogFile
    output << log << std::endl;

    // CLose the LogFile
    output.close();
}

// Assignment Operator
LogObserver &LogObserver::operator=(const LogObserver &s1) {
    return *this;
}

// Copy Constructor
LogObserver::LogObserver(const LogObserver &s1) {

}

// Stream Output Operator
std::ostream &operator<<(std::ostream &out, const LogObserver &subject) {
    out << "{LOGOBSEREVER CLASS}";
    return out;
}
