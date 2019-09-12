#include "logger.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

Logger::Logger(std::string ff, char c) noexcept
    : sep_(c)
{
    if(ff.empty()){   /// если файл не задан
       p_ofs_ = &std::cout;
    }else{
        try{ // перехватим исключение
             out_stream = std::make_shared<std::ofstream>(ff,std::ofstream::out /*| std::ofstream::app*/);
             p_ofs_ = out_stream.get();
        }catch(std::exception &ex){
            std::string str_exc(ex.what());
            str_exc += __FILE__ + std::to_string( __LINE__);
            LOG(NULL, str_exc.c_str());
        }
    }
    std::string str;    str += __FILE__ + std::to_string( __LINE__);    LOG(NULL, str.c_str());
    LOG(NULL,__PRETTY_FUNCTION__);
}

const Logger& Logger::operator ()(const std::string&s ) const {
    if(p_ofs_ != nullptr){
        *p_ofs_ << s << sep_;
    }
    return *this;
}

const Logger& Logger::operator ()(std::ostream& os, const std::string&s ) const {
    os << s << sep_;
    return *this;
}

const Logger& Logger::operator << (const std::string&s ) const {
    if(p_ofs_ != nullptr){
        *p_ofs_ << s << sep_;
    }
    return *this;
}

// Logger может быть синглтоном
// writeLogMessage единственная функция которая будет его применять будет о нём знать
//
void set_log_level(){}
void get_log_level(){}

void writeLogMessage(LogLevel logLevel, const char* message)
{
    std::ostringstream ss;
    ss << message << std::endl;
    std::ostream* out = (logLevel <= LOG_LEVEL_WARNING) ? &std::cerr : &std::cout;
    (*out) << ss.str();
    if (logLevel <= LOG_LEVEL_WARNING)
        (*out) << std::flush;
}















//  const int threadID = cv::utils::getThreadID();
//    std::ostringstream ss;
//    switch (logLevel)
//    {
//    case LOG_LEVEL_FATAL:   ss << "[FATAL:" << threadID << "] " << message << std::endl; break;
//    case LOG_LEVEL_ERROR:   ss << "[ERROR:" << threadID << "] " << message << std::endl; break;
//    case LOG_LEVEL_WARNING: ss << "[ WARN:" << threadID << "] " << message << std::endl; break;
//    case LOG_LEVEL_INFO:    ss << "[ INFO:" << threadID << "] " << message << std::endl; break;
//    case LOG_LEVEL_DEBUG:   ss << "[DEBUG:" << threadID << "] " << message << std::endl; break;
//    case LOG_LEVEL_VERBOSE: ss << message << std::endl; break;
//    default:
//        return;
//    }
//#ifdef __ANDROID__
//    int android_logLevel = ANDROID_LOG_INFO;
//    switch (logLevel)
//    {
//    case LOG_LEVEL_FATAL:   android_logLevel = ANDROID_LOG_FATAL; break;
//    case LOG_LEVEL_ERROR:   android_logLevel = ANDROID_LOG_ERROR; break;
//    case LOG_LEVEL_WARNING: android_logLevel = ANDROID_LOG_WARN; break;
//    case LOG_LEVEL_INFO:    android_logLevel = ANDROID_LOG_INFO; break;
//    case LOG_LEVEL_DEBUG:   android_logLevel = ANDROID_LOG_DEBUG; break;
//    case LOG_LEVEL_VERBOSE: android_logLevel = ANDROID_LOG_VERBOSE; break;
//    default:
//        break;
//    }
//    __android_log_print(android_logLevel, "OpenCV/" CV_VERSION, "%s", ss.str().c_str());
//#endif
//    std::ostream* out = (logLevel <= LOG_LEVEL_WARNING) ? &std::cerr : &std::cout;
//    (*out) << ss.str();
//    if (logLevel <= LOG_LEVEL_WARNING)
//        (*out) << std::flush;



















