#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <sstream>
#include <cstdio>
#include <cstring>
#include <stdexcept>

// strips filepath to get filename
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// Enumeration representing different logging levels.
enum TLoggerLevel { L_ERROR, L_WARNING, L_INFO, L_DEBUG, DEBUG1, DEBUG2, DEBUG3 };

// String representations of the logging levels
static const char* TLoggerLevelString[] =
{ "ERROR", "WARNING", "INFO", "DEBUG",
"DEBUG1", "DEBUG2", "DEBUG3" };

// Enumeration representing ANSI color codes for text color in the console.
enum TColorCodes {
    RESET, WHITE, RED, GREEN, YELLOW, BLUE, MAGENTA,
    CYAN, GRAY, BOLD_RED, BOLD_GREEN, BOLD_YELLOW
};

// String representations of ANSI color codes.
static const char* TColorCodesString[] = {
  "\033[0m",      // RESET
  "\033[1m",      // WHITE
  "\033[0;31m",   // RED
  "\033[0;32m",   // GREEN
  "\033[0;33m",   // YELLOW
  "\033[0;34m",   // BLUE
  "\033[0;35m",   // MAGENTA
  "\033[0;36m",   // CYAN
  "\033[1;30m",   // GRAY
  "\033[1;31m",   // BOLD_RED
  "\033[1;32m",   // BOLD_GREEN
  "\033[1;33m"    // BOLD_YELLOW
};

// Default reporting level for logging.
#ifndef REPORTING_LEVEL
#define REPORTING_LEVEL L_INFO
#endif

// Logging macros to be used for logging.
#define LOG(LEVEL) \
  if (LEVEL <= REPORTING_LEVEL) \
    Log().get(LEVEL) << TLoggerLevelString[LEVEL] << " " << __TIME__ \
                     << " [" << __FILENAME__ << ":" << __LINE__ << "] "

#define LOG_COLOR(LEVEL, COLOR) \
  if (LEVEL <= REPORTING_LEVEL) \
    Log().getColor(LEVEL, COLOR) << TLoggerLevelString[LEVEL] << " " << __TIME__ \
                     << " [" << __FILENAME__ << ":" << __LINE__ << "] "

#define LOG_IF(LEVEL, COND) if (COND) LOG(LEVEL)
#define LOG_IF_COLOR(LEVEL, COND, COLOR) if (COND) LOG_COLOR(LEVEL, COLOR)

/**
* @brief Logging engine class that uses logging level to log to stderr.
*/
class Log {
private:
    TLoggerLevel messageLevel;
    TColorCodes colorCode;
    std::ostringstream os;

public:
    /**
    * @brief Constructor initializes default logging level and color code.
    */
    Log() :messageLevel(L_INFO), colorCode(RESET) {}

    /**
    * @brief Get a reference to the output stream for logging.
    */
    std::ostringstream& get(TLoggerLevel level = L_INFO) {
        messageLevel = level;
        return os;
    }

    /**
    * @brief Get a reference to the output stream with specified color for logging.
    */
    std::ostringstream& getColor(
        TLoggerLevel level = L_INFO,
        TColorCodes color = RESET) {
        messageLevel = level;
        colorCode = color;
        return os;
    }

    /**
    * @brief Destructor flushes the log and prints it to stderr.
    */
    ~Log() {
        if (messageLevel <= REPORTING_LEVEL) {
            os << std::endl;
            fprintf(stderr, "%s%s%s",
                TColorCodesString[colorCode],
                os.str().c_str(),
                TColorCodesString[RESET]);
            fflush(stderr);
        }
    }
};

/**
* @brief Macro for throwing a runtime error with context details.
*/
#define throwRuntimeError(x) \
  std::stringstream ss; \
  ss << "[" << __TIME__ << ":" << __FILENAME__ << ":" << __LINE__ << "] " \
      << x; \
  throw std::runtime_error(ss.str());


#endif // _LOGGER_H_