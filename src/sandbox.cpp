#include "slou.hpp"

int main()
{
    std::string format = "{message}";

    slou::Logger logger("test");

    logger.Log(logger.SUCCESS,  "Successfully successed!");
    logger.Log(logger.INFO,     "Successfully info'ed!");
    logger.Log(logger.WARNING,  "Successfully warned!");
    logger.Log(logger.ERROR,    "Successfully error'ed!");
    logger.Log(logger.CRITICAL, "Successfully critical'ed!");
}
