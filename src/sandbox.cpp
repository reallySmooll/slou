#include "slou.hpp"

int main()
{
    std::string format = "{level} - {message}";

    slou::Logger logger("slou", "%x", true, true);

    //logger.Log(logger.SUCCESS,  "Successfully successed!");
    //logger.Log(logger.INFO,     "Successfully info'ed!");
    //logger.Log(logger.WARNING,  "Successfully warned!");
    //logger.Log(logger.ERROR,    "Successfully error'ed!");
    //logger.Log(logger.CRITICAL, "Successfully critical'ed!");

    logger.Log(logger.INFO, "This is being logged onto the screen!");

    logger.logToScreen = false;

    logger.Log(logger.INFO, "This isn't being logged onto the screen!");
}
