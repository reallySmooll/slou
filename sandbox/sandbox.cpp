#include <slou/slou.hpp>

#include <iostream>

int main()
{
    slou::Logger logger("slou", "%X", true, true);

    logger.Log(logger.CRITICAL, "Hello, world!");

    return 0;
}
