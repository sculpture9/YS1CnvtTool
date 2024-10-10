#pragma once
#include <string>

long UTF82Unicode(const std::string &str, std::wstring &wstr);

long Unicode2UTF8(const std::wstring &wstr, std::string &str);