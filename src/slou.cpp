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
     * \param projectName constant reference to a string representing the project name. (defaults to "slou")
     */
    Logger::Logger(const std::string& projectName)
        : _projectName(projectName),
          _timeFormat("%X"),
          _logToFile(true),
          _logToScreen(false),
          _logFilename("slou.log"),
          _moduleName("main"),
          _format("{projectName} - [{moduleName} | {level}] ({time}): {message}")
    {
        if (std::filesystem::exists(_logFilename))
            std::filesystem::remove(_logFilename);
    }

    /** \brief Default Logger class deconstructor.
     *
     * The deconstructor does nothing.
     */
    Logger::~Logger() { }

    /** \brief Changes the name of your module (e.g. class name).
     *
     * \param moduleName constant reference to a string representing the name of your module (e.g. class name). (defaults to "main")
     */
    Logger& Logger::moduleName(const std::string& moduleName)
    { _moduleName  = moduleName;  return *this; }

    /** \brief Changes the time format.
     *
     * For more ways of formatting date and time, check out: https://en.cppreference.com/w/cpp/io/manip/put_time
     *
     * \param timeFormat constant character pointer representing the date and/or time format. (defaults to "%X" which is the localized time representation, meaning the current hour, minute and second, locale dependent)
     */
    Logger& Logger::timeFormat(const char* timeFormat)
    { _timeFormat  = timeFormat;  return *this; }

    /** \brief Changes whether the logs should be saved to a file.
     *
     * \param logToFile boolean representing the need to log to a file. (defaults to "true")
     */
    Logger& Logger::logToFile(bool logToFile)
    { _logToFile   = logToFile;   return *this; }

    /** \brief Changes whether the logs should be displayed in the terminal.
     *
     * \param logToScreen boolean representing the need to log to the screen. (defaults to "false")
     */
    Logger& Logger::logToScreen(bool logToScreen)
    { _logToScreen = logToScreen; return *this; }

    /** \brief Changes the log file path and name.
     *
     * \param logFilename constant reference to a string representing the path and name of the log file. (defaults to "slou.log")
     */
    Logger& Logger::logFilename(const std::string& logFilename)
    { _logFilename = logFilename; return *this; }

    /** \brief Changes the log format.
     *
     * \param format constant reference to a string representing the custom log format. (defaults to "{projectName} - [{moduleName} | {level}] ({time}): {message}")
     */
    Logger& Logger::format(const std::string& format)
    { _format      = format;      return *this; }

    /** \brief Function logs the passed in message variable to the terminal and/or a file.
     *
     * \param level constant reference to a string representing the level of severity of the log message.
     * \param message constant reference to a string representing the message that is supposed to be logged.
     */
    void Logger::Log(const std::string& level, const std::string& message)
    {
        _level   = level;
        _message = message;

        if (_logToFile)
        {
            logFile.open(_logFilename, logFile.app);

            logFile << Format(_format) << std::endl;

            logFile.close();
        }

        if (_logToScreen && colorTerminalOutput)
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
        } else if (_logToScreen && !colorTerminalOutput)
            std::cout << Format(_format) << std::endl;

        if (!_logToScreen && !_logToFile)
            throw std::runtime_error("At least one of the variables (logToScreen or logToFile) must be true!");
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
     * - {moduleName} - replaced for moduleName variable
     *
     * \param format string representing the log format using the variables listed above.
     */
    std::string Logger::Format(std::string format)
    {
        size_t pos;

        pos = format.find("{projectName}");
        if (pos != std::string::npos)
            format.replace(pos, 13, _projectName);

        pos = format.find("{level}");
        if (pos != std::string::npos)
            format.replace(pos, 7, _level);

        pos = format.find("{time}");
        if (pos != std::string::npos)
            format.replace(pos, 6, CurrentDateAndTime(_timeFormat));

        pos = format.find("{message}");
        if (pos != std::string::npos)
            format.replace(pos, 9, _message);

        pos = format.find("{moduleName}");
        if (pos != std::string::npos)
            format.replace(pos, 12, _moduleName);

        return format;
    }
}
