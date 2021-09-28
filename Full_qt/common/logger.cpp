#include "logger.h"

#include <sstream>
#include <iostream>
#include <fstream>

#include <exception>

#include <ctime>
#include <stdarg.h>
#include<unistd.h>
#include<sys/types.h>
#include <pwd.h>

#include <iomanip>

#define r_inst() Logger::get_inst()

class m_ofstream :
        public std::ofstream
{
public:
    m_ofstream() :
        std::ofstream ()
    {
        LOG_WARNING (NULL,__PRETTY_FUNCTION__) ;
    }

    m_ofstream(const  m_ofstream&)                = delete ;
    m_ofstream& operator = (const  m_ofstream&)   = delete ;

    m_ofstream(m_ofstream&& rhs) :
        std::ofstream (std::move(rhs))
    {
        LOG_WARNING (NULL,__PRETTY_FUNCTION__);
    }

    m_ofstream& operator = ( m_ofstream&& rhs)  {
        LOG_WARNING (NULL,__PRETTY_FUNCTION__);
        std::ofstream::operator=(std::move(rhs));
        return *this;
    }

    ~m_ofstream(){
        LOG_WARNING (NULL,__PRETTY_FUNCTION__);
    }

};

Logger::Logger(){
   pw = ::getpwuid(::getuid());
   log_dir += pw->pw_dir;
   log_dir += "/.full_qt";
}

Logger::~Logger(){
    for (auto kvp: map_oss) {
        delete kvp.second;
    }
}

Logger& Logger::get_inst(){
    static Logger ml;
    return ml;
}

std::ostream* Logger::at(std::string str)try
{
    std::string file = log_dir + '/' + str;
    try {
        return &map_osf.at(file);
    } catch (std::exception& ex) {
        ex.what();
        auto kvs = map_osf.emplace(file,std::ofstream()); /// move constructor
        if(kvs.second){
            if(!kvs.first->second.is_open()){
                kvs.first->second.open(file, std::ios_base::out|std::ios_base::trunc);
            }
            return &kvs.first->second;
        }

        std::ofstream *tt = new std::ofstream();
        if(tt!=nullptr && !tt->is_open())
            tt->open(file, std::ios_base::out|std::ios_base::trunc);
        auto kvp = map_oss.insert({file, tt});
        return map_oss.at(file);
    }
} catch(std::exception& ex){
    ex.what();
}

void log_write(int logt, const char *fmt, ...) {
  // проверка
  va_list ap;
  if (!fmt || !*fmt)
    return;

  for (int l = 1; l <= 16; l <<= 1) {
    if (logt & l) {
      va_start(ap, fmt);
      log_write(l, fmt, ap);
      va_end(ap);
    }
  }
  return;
}

void writeLogMessage(LogLevel logLevel, const char* message)
{
   //const int threadID = cv::utils::getThreadID();

    std::time_t rst = std::time(nullptr);
    std::tm tm_ = *std::localtime(&rst);
    std::ostringstream sst ;
    sst <<" ["<< std::put_time(&tm_,"%F") << " " << std::put_time(&tm_,"%T") << "] ";

    std::ostringstream ss;
    switch (logLevel)
    {
    case LOG_LEVEL_FATAL:   ss << "[FATAL:" <<  "] " << sst.str() << message << std::endl; break;
    case LOG_LEVEL_ERROR:   ss << "[ERROR:" <<  "] " << sst.str() << message << std::endl; break;
    case LOG_LEVEL_WARNING: ss << "[ WARN:" <<  "] " << sst.str() << message << std::endl; break;
    case LOG_LEVEL_INFO:    ss << "[ INFO:" <<  "] " << sst.str() << message << std::endl; break;
    case LOG_LEVEL_DEBUG:   ss << "[DEBUG:" <<  "] " << sst.str() << message << std::endl; break;
    case LOG_LEVEL_VERBOSE: ss << sst.str() << message << std::endl; break;
    case LOG_LEVEL_SILENT: return;
    }

    std::ostream* out{nullptr};

    switch (logLevel) {
    case LOG_LEVEL_FATAL:
        out = &std::cerr;
        break;
    case LOG_LEVEL_WARNING:
    case LOG_LEVEL_INFO:
    case LOG_LEVEL_ERROR:
        out = r_inst().at("full_qt.err");
        break;
    default:
        out = &std::cout;
        break;
    }

    (*out) << ss.str();
    if (logLevel <= LOG_LEVEL_INFO)
        (*out) << std::flush;
}

void writeLogMessageEx(LogLevel logLevel, const char* tag, const char* file, int line, const char* func, const char* message)
{
    std::ostringstream strm;

    if (tag){
        strm << tag << " ";
    }
    if (file){
        strm << "[" << file << "] ";
    }
    if (line > 0){
        strm << "(" << line << ") ";
    }
    if (func){
        strm << "[" << func << "] ";
    }
    if (message){
        strm << "[" << message << "] ";
    }
    writeLogMessage(logLevel, strm.str().c_str());
}
