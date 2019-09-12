#ifndef LOGGER_H
#define LOGGER_H

#include <ostream>
#include <sstream>
#include <memory>

#define watch(x) std::cout << (#x) << " : " << x << "\n";

enum LogLevel { LOG_LEVEL_SILENT = 0,              //!< for using in setLogVevel() call
                LOG_LEVEL_FATAL = 1,               //!< Fatal (critical) error (unrecoverable internal error)
                LOG_LEVEL_ERROR = 2,               //!< Error message
                LOG_LEVEL_WARNING = 3,             //!< Warning message
                LOG_LEVEL_INFO = 4,                //!< Info message
                LOG_LEVEL_DEBUG = 5,               //!< Debug message. Disabled in the "Release" build.
                LOG_LEVEL_VERBOSE = 6,             //!< Verbose (trace) messages. Requires verbosity level. Disabled in the "Release" build.
              } ;

void writeLogMessage(LogLevel logLevel, const char* message);

// первый вариант применяю где хочу пишет в std::cerr or std::cout
#define LOG(tag, ...)   for(;;) { std::stringstream ss; ss << __VA_ARGS__; writeLogMessage(LOG_LEVEL_INFO, ss.str().c_str()); break; }

// второй вариант объект Logger создаю в каждом классе по необходимости
class Logger
{
public:

    explicit Logger(std::string ff = "", char c = '\n') noexcept ;

    Logger(const Logger&)                 = delete;
    Logger(Logger&&)                      = delete;
    Logger& operator = (const Logger&)    = delete;
    Logger& operator = (Logger&&)         = delete;
    ~Logger()                             = default;

    // пишу по умолчанию куда пишет Logger
    const Logger& operator ()(const std::string&s ) const ;

    // пишу в файл файлов можно создавать сколько угодно
    const Logger& operator ()(std::ostream& os, const std::string&s ) const ;

    const Logger& operator << (const std::string&s ) const ;

private:
    std::shared_ptr<std::ostream> out_stream;
    std::ostream *p_ofs_ = {nullptr};

    //    std::ostream &os_;
    char sep_;
};

#endif // LOGGER_H
