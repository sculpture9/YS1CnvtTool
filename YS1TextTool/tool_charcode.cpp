#include "tool_charcode.h"
#include "Windows.h"

long UTF82Unicode(const std::string &str, std::wstring &wstr)
{
    long wl = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size(), 0, 0);
    wstr.clear();
    wstr.resize(wl);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size(), &wstr[0], wl);
    return wl;
}

long Unicode2UTF8(const std::wstring &wstr, std::string &str)
{
    long sl = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), 0, 0, NULL, NULL);
    str.clear();
    str.resize(sl);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), &str[0], sl, NULL, NULL);
    return sl;
}
