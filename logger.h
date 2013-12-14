#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

class logger
{

    logger();
    logger(const logger&);
    logger& operator=(const logger&);
    ~logger();


public:
    static logger& instance(){
        static logger instance;
        return instance;
    }

    void log(std::string message);
};

#endif // LOGGER_H
