#include "glog.h"

#include <Shlwapi.h>    //检测文件路径是否存在
#include <QDebug>
#include <stdarg.h> //函数可变参

#include "base/errorcode.h"


GLog::GLog()
{
    initFile();
    setLogMode(GLogMode::File);
    addFirstLog();
}

GLog::~GLog()
{

}

int GLog::addLog(const char *file, const int line, GLogLevel level, const char *message){

    //日志信息格式：
    //[2023-02-25][23:40:20.23][Error][File][Line][GLog::addLog][add success]
    char t_msg[CHAR_MAX];

    //日期和时间
    SYSTEMTIME t_sys;
    GetLocalTime(&t_sys);
    char t_time[CHAR_MAX];
    sprintf(t_time, "[%4d-%02d-%02d][%02d:%02d:%02d.%03d]", t_sys.wYear, t_sys.wMonth, t_sys.wDay, t_sys.wHour,
            t_sys.wMinute, t_sys.wSecond, t_sys.wMilliseconds);
    sprintf(t_msg, "%s", t_time);
    m_log_msg=t_msg;

    //日志等级
    if(level==GLogLevel::Debug){
        sprintf(t_msg, "[%s]", "Debug");
    }else if(level==GLogLevel::Info){
        sprintf(t_msg, "[%s]", "Info");
    }else if(level==GLogLevel::Warn){
        sprintf(t_msg, "[%s]", "Warn");
    }else if(level==GLogLevel::Error){
        sprintf(t_msg, "[%s]", "Error");
    }
    m_log_msg+=t_msg;

    //日志所在文件
    sprintf(t_msg, "[%s]", file);
    m_log_msg+=t_msg;

    //日志所在行
    sprintf(t_msg, "[%d]", line);
    m_log_msg+=t_msg;

    //用户信息
    m_log_msg+=message;

    //将message提取
    sprintf(t_msg, "\n");
    m_log_msg+=t_msg;

    int rec=outLog();
    if(rec!=ErrorCode::Success){
        return rec;
    }
    return ErrorCode::Success;
}

int GLog::initFile(){

    //检测glog目录是否存在，路径存在则返回真
    if(!PathIsDirectoryW(L"./glog/")){
        //创建目录，创建成功返回真
        if(!CreateDirectoryW(L"./glog/", NULL)){
            return ErrorCode::GLog_CreateDirFail;
        }
    }

    //获取当前的日期作为日志文件名
    SYSTEMTIME t_sys;
    GetLocalTime(&t_sys);
    char t_time[CHAR_MAX];
    sprintf_s(t_time, "%4d_%02d_%02d", t_sys.wYear, t_sys.wMonth, t_sys.wDay);
    char t_file[CHAR_MAX];
    sprintf(t_file, "./glog/glog_%s.log", t_time);

    //将char转wchar
    DWORD t_file_len = MultiByteToWideChar(CP_ACP, 0, t_file, -1, NULL, 0);
    wchar_t* t_wfile = new wchar_t[t_file_len];
    MultiByteToWideChar(CP_ACP, 0, t_file, -1, t_wfile, t_file_len);

    //创建或打开文件（设置了追加模式）
    m_handle=CreateFile(t_wfile,
                        GENERIC_READ | GENERIC_WRITE,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
    if(m_handle==INVALID_HANDLE_VALUE){
        return ErrorCode::GLog_CreateFileFail;
    }

    return ErrorCode::Success;
}

int GLog::setLogMode(GLogMode target){

    m_mode=target;
    return ErrorCode::Success;
}

int GLog::outLog(){

    if (m_mode==GLogMode::File)
    {
        SetFilePointer(m_handle, 0, NULL, FILE_END);
        DWORD dwBytesWritten = 0;
        if(!WriteFile(m_handle, m_log_msg.c_str(), m_log_msg.length(), &dwBytesWritten, NULL)){
            FlushFileBuffers(m_handle);
            m_log_msg.clear();
            return GLog_WriteToFileFail;
        }
        FlushFileBuffers(m_handle);
    }
    else if (m_mode==GLogMode::Console)
    {
        printf("%s", m_log_msg.c_str());
        //输出缓存区（否则只会在程序关闭时打印到控制台）
        fflush(stdout);
    }

    // 清除存储信息
    m_log_msg.clear();
    return ErrorCode::Success;
}

int GLog::addFirstLog(){

    //获取日期时间
    SYSTEMTIME t_sys;
    GetLocalTime(&t_sys);
    char t_time[CHAR_MAX];
    sprintf(t_time, "%4d-%02d-%02d %02d:%02d:%02d.%03d", t_sys.wYear, t_sys.wMonth, t_sys.wDay, t_sys.wHour,
            t_sys.wMinute, t_sys.wSecond, t_sys.wMilliseconds);
    char t_msg[CHAR_MAX];
    sprintf(t_msg, "\nNew Program Start When %s\n", t_time);

    m_log_msg=t_msg;
    int rec=outLog();
    if(rec!=ErrorCode::Success){
        return rec;
    }
    return ErrorCode::Success;
}

char *GLog::getUserMsg(const char *format, ...){
    //实现如printf一样的字符串+多个不定参的字符串组合
    char t_buffer[GLOG_MSG_MAX_LEN]={0};
    va_list t_pos;
    va_start(t_pos, format);
    vsprintf_s(t_buffer, format, t_pos);
    va_end(t_pos);
    m_user_msg = t_buffer;
    return m_user_msg;
}
