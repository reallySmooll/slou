/** \file slou.hpp
 * \brief The most important file in this library.
 */

#pragma once

#include <string>
#include <fstream>

#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_SLOU
    #define SLOU_PUBLIC __declspec(dllexport)
  #else
    #define SLOU_PUBLIC __declspec(dllimport)
  #endif
#else
  #ifdef BUILDING_SLOU
      #define SLOU_PUBLIC __attribute__ ((visibility ("default")))
  #else
      #define SLOU_PUBLIC
  #endif
#endif

/** \brief "slou" namespace. */
namespace slou
{
    /** \brief Class creates the logger that logs everything to the screen and/or file. */
    class SLOU_PUBLIC Logger
    {
        public:
            explicit Logger(const std::string& projectName="slou", const char* timeFormat="%X", bool logToFile=true, bool logToScreen=false, const std::string& logFilename="slou.log", const std::string& format="{projectName} - [{level}] ({time}): {message}");
            ~Logger();

            void Log(const std::string& level, const std::string& message);

            const std::string SUCCESS  = "SUCCESS";  ///< Success level indicates that an operation was successful.
            const std::string INFO     = "INFO";     ///< Info level displays basic information.
            const std::string WARNING  = "WARNING";  ///< Warning level indicates that there's something wrong with the program but doesn't require immediate attention.
            const std::string ERROR    = "ERROR";    ///< Error level indicates that there's something wrong with the program requires attention.
            const std::string CRITICAL = "CRITICAL"; ///< Critical level indicates that there's something wrong with the program and requires immediate attention.

            std::string projectName;                 ///< Name of your project. (defaults to "slou")

            const char* timeFormat;                  ///< Date and/or time format. (defaults to "%X", which means the current hour, minute and second)

            bool logToFile;                          ///< Should the logger put logs to a file. (defaults to "true")
            bool logToScreen;                        ///< Should the logger display logs to a screen. (defaults to "false")

            std::string logFilename;                 ///< Path and name of the log file. (defaults to "slou.log")

            bool colorTerminalOutput = true;         ///< Should logs in the terminal be colored. (defaults to "true")
        private:
            std::string CurrentDateAndTime(const char* timeFormat);
            std::string Format(std::string format);

            const std::string RESET    = "\033[0m";  ///< Reset color resets all of the colors to the terminal default.
            const std::string RED      = "\033[31m"; ///< Red color paints output red. Used in critical errors.
            const std::string GREEN    = "\033[32m"; ///< Green color paints output green. Used when something is successful.
            const std::string WHITE    = "\033[37m"; ///< White color paints output white. Used when displaying basic information.
            const std::string L_RED    = "\033[91m"; ///< Light red color paints output light red. Used in errors.
            const std::string L_YELLOW = "\033[93m"; ///< Light yellow color paints output light yellow. Used in warnings.

            std::fstream logFile;                    ///< The file used for logging.

            std::string _format;                     ///< Custom log format
            std::string _level;                      ///< Log level
            std::string _message;                    ///< Log message
    };
}
