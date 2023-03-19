/** \file slou.cpp
 * \brief Definition file for the "Logger" class.
 */

#include "slou.hpp"

#include <ctime>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <chrono>
#include <string>

namespace slou
{
    /** \brief Default Logger class constructor that initializes all passed in variables for use.
     *
     * The constructor checks if the log file exists and if it does, the constructor removes the file.
     *
     * For more ways of formatting date and time, check out: https://en.cppreference.com/w/cpp/io/manip/put_time
     *
     * \param projectName constant reference to a string representing the project name. (defaults to "slou")
     * \param timeFormat constant character pointer representing the date and/or time format. (defaults to "%X" which is the localized time representation, meaning the current hour, minute and second, locale dependent)
     * \param logToFile boolean representing the need to log to a file. (defaults to "true")
     * \param logToScreen boolean representing the need to log to the screen. (defaults to "false")
     * \param logFilename constant reference to a string representing the path and name of the log file. (defaults to "slou.log")
     * \param format constant reference to a string representing the custom log format. (defaults to "{projectName} - [{level}] ({time}): {message}")
     */
    Logger::Logger(const std::string& projectName, const char* timeFormat, bool logToFile, bool logToScreen, const std::string& logFilename,const std::string& format)
        : projectName(projectName),
          timeFormat(timeFormat),
          logToFile(logToFile),
          logToScreen(logToScreen),
          logFilename(logFilename),
          _format(format)
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
     * \param level constant reference to a string representing the level of severity of the log message.
     * \param message constant reference to a string representing the message that is supposed to be logged.
     */
    void Logger::Log(const std::string& level, const std::string& message)
    {
        _level   = level;
        _message = message;

        if (logToFile)
        {
            logFile.open(logFilename, logFile.app);

            logFile << Format(_format) << std::endl;

            logFile.close();
        }

        if (logToScreen && colorTerminalOutput)
        {
            if (level == SUCCESS)
                std::cout << GREEN    << Format(_format) << RESET << std::endl;
            else if (level == INFO)
                std::cout << WHITE    << Format(_format) << RESET << std::endl;
            else if (level == WARNING)
                std::cout << L_YELLOW << Format(_format) << RESET << std::endl;
            else if (level == ERROR)
                std::cout << L_RED    << Format(_format) << RESET << std::endl;
            else if (level == CRITICAL)
                std::cout << RED      << Format(_format) << RESET << std::endl;
        } else if (logToScreen && !colorTerminalOutput)
            std::cout << Format(_format) << std::endl;

        if (!logToScreen && !logToFile)
            throw std::runtime_error("At least one of the variables (shouldLogToScreen or shouldLogToFile) must be true!");
    }

    /** \brief Function gets the current date and time and displays it in the format passed to the variable.
     *
     * \param timeFormat constant character pointer representing the format of the date and/or time.
     */
    std::string Logger::CurrentDateAndTime(const char* timeFormat)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t time_now = std::chrono::system_clock::to_time_t(now);
        std::tm tm_now;

#ifdef _WIN32
        localtime_s(&tm_now, &time_now);
#else
        localtime_r(&time_now, &tm_now);
#endif // _WIN32

        std::stringstream ss;
        ss << std::put_time(&tm_now, timeFormat);

        return ss.str();
    }

    /** \brief Function finds strings in a custom format and replaces them with variable values.
     *
     * Replaced strings are:
     * - {projectName} - replaced for projectName variable
     * - {level} - replaced for private level variable
     * - {time} - replaced for timeFormat variable
     * - {message} - replaced for private message variable
     *
     * \param format string representing the log format using the variables listed above.
     */
    std::string Logger::Format(std::string format)
    {
        size_t pos;

        pos = format.find("{projectName}");
        if (pos != std::string::npos)
            format.replace(pos, 13, projectName);

        pos = format.find("{level}");
        if (pos != std::string::npos)
            format.replace(pos, 7, _level);

        pos = format.find("{time}");
        if (pos != std::string::npos)
            format.replace(pos, 6, CurrentDateAndTime(timeFormat));

        pos = format.find("{message}");
        if (pos != std::string::npos)
            format.replace(pos, 9, _message);

        return format;
    }
}
