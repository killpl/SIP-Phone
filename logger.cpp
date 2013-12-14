#include "logger.h"
#include <syslog.h>


logger::logger()
{
    openlog("Softphone", LOG_PID, LOG_USER);
}

logger::~logger(){
    closelog();
}

void logger::log(std::string message){
    syslog(LOG_INFO, message.c_str());
}
