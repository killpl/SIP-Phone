#include "logger.h"

logger::logger()
{
}


void logger::log(int level, std::string message){
    std::cout << "[" << level << "]\t" << message << std::endl;
}
