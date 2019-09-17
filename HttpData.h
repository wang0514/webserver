//
// Created by wangkaikai on 19-6-27.
//

#ifndef WEBSERVER_HTTPDATA_H
#define WEBSERVER_HTTPDATA_H

#include <unordered_map>
#include <iostream>
#include <string>
#include <unistd.h>


class EventLoop;
class TimeNode;
class Channel;

/**
 * 枚举处理类
 */
enum ProcessState{
    STATE_PARSE_URL = 1,
    STATE_PARSE_HEADERS,
    STATE_RECV_BODY,
    STATE_ANALYSIS,
    STATE_FINISH
};

enum URLState{
    PARSE_URL_AGAIN = 1,
    PARSE_URL_ERROR,
    PASE_URL_SUCCESS
};

enum AnalysisState
{
    ANALYSIS_SUCCESS = 1,
    ANALYSIS_ERROR
};

enum ParseState
{
    H_START = 0,
    H_KEY,
    H_COLON,
    H_SPACES_AFTER_COLON,
    H_VALUE,
    H_CR,
    H_LF,
    H_END_CR,
    H_END_LF
};

enum ConnectionState
{
    H_CONNECTED = 0,
    H_DISCONNECTING,
    H_DISCONNECTED
};

enum HttpMethod
{
    METHOD_POST = 1,
    METHOD_GET,
    METHOD_HEAD
};

enum HttpVersion
{
    HTTP_10 = 1,
    HTTP_11
};

class MimeType{
private:
    static void init();
    static std::unordered_map<std::string,std::string> mime;
    MimeType();
    MimeType(const MimeType &m);
    static pthread_once_t once_control;
public:

    static std::string getMime(const std::string &suffix);

};
#endif //WEBSERVER_HTTPDATA_H
