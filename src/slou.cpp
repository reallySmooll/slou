/** \file slou.cpp
 * \brief Definition file for the "Logger" class.
 */

#include "include/slou/slou.hpp"

#include <iostream>
#include <filesystem>
#include <stdexcept>

namespace slou
{
    /** \brief Default Logger class constructor that initializes all passed in variables for use.
     *
     * The constructor checks if the log file exists and if it does, the constructor removes the file.
     *
     * For more ways of formatting the date and time, check out: https://cplusplus.com/reference/ctime/strftime/
     *
     * \param projectName string representing the project name. (defaults to "slou")
     * \param format string representing the date and/or time format. (defaults to "%X" which means the current hour, minute and second)
     * \param shouldLogToFile boolean representing the need to log to a file. (defaults to "true")
     * \param shouldLogToScreen boolean representing the need to log to the screen. (defaults to "false")
     * \param logFilename string representing the path and name of the log file. (defaults to "slou.log")
     */
    Logger::Logger(std::string projectName, const char* format, bool shouldLogToFile, bool shouldLogToScreen, std::string logFilename)
        : projectName(projectName),
          format(format),
          shouldLogToFile(shouldLogToFile),
          shouldLogToScreen(shouldLogToScreen),
          logFilename(logFilename)
    {
        if (std::filesystem::exists(logFilename))
            std::filesystem::remove(logFilename);
    }

    /** \brief Default Logger class deconstructor.
     *
     * The deconstructor does nothing.
     */
    Logger::~Logger() { }

    /** \brief Function logs the passed in message variable to the terminal and/or a file.
     *
     * \param level string representing the level of severity of the log message.
     * \param message string representing the message that is supposed to be logged.
     */
    void Logger::Log(std::string level, std::string message)
    {
        if (shouldLogToFile)
        {
            logFile.open(logFilename, logFile.app);

            logFile << projectName << " - [" << level << "] (" << CurrentDateAndTime(format) << "): " << message << std::endl;

            logFile.close();
        }

        if (shouldLogToScreen)
        {
            if (level == SUCCESS)
                std::cout << GREEN    << projectName << " - [" << level << "] (" << CurrentDateAndTime(format) << "): " << message << RESET << std::endl;
            else if (level == INFO)
                std::cout << WHITE    << projectName << " - [" << level << "] (" << CurrentDateAndTime(format) << "): " << message << RESET << std::endl;
            else if (level == WARNING)
                std::cout << L_YELLOW << projectName << " - [" << level << "] (" << CurrentDateAndTime(format) << "): " << message << RESET << std::endl;
            else if (level == ERROR)
                std::cout << L_RED    << projectName << " - [" << level << "] (" << CurrentDateAndTime(format) << "): " << message << RESET << std::endl;
            else if (level == CRITICAL)
                std::cout << RED      << projectName << " - [" << level << "] (" << CurrentDateAndTime(format) << "): " << message << RESET << std::endl;
        }

        if (!shouldLogToScreen && !shouldLogToFile)
            throw std::runtime_error("At least one of the variables (shouldLogToScreen or shouldLogToFile) must be true!");
    }

    /** \brief Function gets the current date and time and displays it in the format passed to the variable.
     *
     * \param format string representing the format of the date and/or time.
     */
    std::string Logger::CurrentDateAndTime(const char* format)
    {
        time_t now = time(0);
        struct tm    tstruct;
        char         buf[80];
        tstruct    = *localtime(&now);

        strftime(buf, sizeof(buf), format, &tstruct);

        return buf;
    }
}
