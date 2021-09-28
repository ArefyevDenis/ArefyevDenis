#ifndef LOGGER_H
#define LOGGER_H

#include <initializer_list>
#include <sstream>
#include <string>

#define DEBUG_MODE

enum LogLevel {
    LOG_LEVEL_SILENT    = 0,            //!< for using in setLogLevel() call
    LOG_LEVEL_FATAL     = 1,            //!< Fatal error
    LOG_LEVEL_ERROR     = 2,            //!< Error message
    LOG_LEVEL_WARNING   = 3,            //!< Warning message
    LOG_LEVEL_INFO      = 4,            //!< Info message
    LOG_LEVEL_DEBUG     = 5,            //!< Debug message.
    LOG_LEVEL_VERBOSE   = 6,            //!< Verbose (trace) messages.
};

void writeLogMessage(LogLevel logLevel, const char* message);

void writeLogMessageEx(LogLevel logLevel, const char* tag, const char* file, int line, const char* func, const char* message);

// а что если  tag это имя файла куда писать
//
// professional C++ Marc Gregoire


#define l_o_g(...) Logger::log(__func__,"(): "),__VA_ARGS__

#define LOG_TAG(tag, msgLevel, ...) \
    for(;;) { \
        std::stringstream logstream; \
        logstream << __VA_ARGS__; \
        writeLogMessageEx( \
            msgLevel, \
            (tag ? nullptr : nullptr), \
            __FILE__, \
            __LINE__, \
            NULL, \
           logstream.str().c_str()); \
        break; \
    }

#define LOG_FATAL(tag, ...)     LOG_TAG(tag, LOG_LEVEL_FATAL,                   __VA_ARGS__)
#define LOG_ERROR(tag, ...)     LOG_TAG(tag, LOG_LEVEL_ERROR,                   __VA_ARGS__)
#define LOG_WARNING(tag, ...)   LOG_TAG(tag, LOG_LEVEL_WARNING,                 __VA_ARGS__)
#define LOG_INFO(tag, ...)      LOG_TAG(tag, LOG_LEVEL_INFO,                    __VA_ARGS__)
#define LOG_VERBOSE(tag, v, ...)LOG_TAG(tag, (LOG_LEVEL_VERBOSE + (int)(v)),    __VA_ARGS__)

#ifdef DEBUG_MODE
#define LOG_DEBUG(tag, ...)     LOG_TAG(tag, LOG_LEVEL_DEBUG,                   __VA_ARGS__)
#else
#define LOG_DEBUG(tag, ...)
#endif

#include <map>

struct passwd;

class Logger
{
public:

    static Logger& get_inst();

    std::ostream* at(std::string);

private:

    Logger();
    Logger(const  Logger&)                = delete ;
    Logger& operator = (const  Logger&)   = delete ;
    Logger(Logger&&)                      = delete ;
    Logger& operator = ( Logger&& )       = delete ;
    ~Logger();

private:

    std::map <std::string, std::ofstream> map_osf;
    std::map <std::string, std::ostream*> map_oss;

    struct passwd *pw{nullptr};
    std::string log_dir;
    std::string log_file;

};

#endif // LOGGER_H
