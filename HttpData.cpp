//
// Created by wangkaikai on 19-6-27.
//

#include "HttpData.h"

pthread_once_t MimeType::once_control = PTHREAD_ONCE_INIT;
std::unordered_map<std::string,std::string>MimeType::mime;

std::string MimeType::getMime(const std::string &suffix) {

}
void MimeType::init() {

}
