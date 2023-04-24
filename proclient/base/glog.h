#ifndef GLOG_H
#define GLOG_H

#include <Windows.h>    //handle句柄、创建文件

#include "base/singleton.h"


#define GLOG_MSG_MAX_LEN 16*1024
#define GLOG_ADD(GLogLevel, format, ...) \
    GLog::getInstance()->addLog(__FILE__, __LINE__, GLogLevel, \
    GLog::getInstance()->getUserMsg(format, ##__VA_ARGS__));

enum GLogLevel{
    Debug,
    Info,
    Warn,
    Error
};

enum GLogMode{
    File,
    Console
};

class GLog : public Singleton<GLog>
{
public:
    GLog();
    ~GLog();
    int addLog(const char *file, const int line, GLogLevel level, const char *message);
    int setLogMode(GLogMode target);
    char *getUserMsg(const char *format, ...);

private:
    GLogMode m_mode;
    HANDLE m_handle;    //windows句柄，操作文件
    std::string m_log_msg="";
    char *m_user_msg;
    int initFile();
    int outLog();
    int addFirstLog();

};

#endif // GLOG_H
