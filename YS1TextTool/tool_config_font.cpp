#include "tool_config_font.h"
#include "ys_define.h"
#include <fstream>
#include <iostream>
#include <map>
#include "tool_charcode.h"

using namespace std;

long GetStrList(std::string path, std::vector<std::string> &result)
{
    ifstream fileReader;
    fileReader.open(path);
    if (!fileReader.is_open()) return -1;
    string line;
    long counter = 0;
    while (getline(fileReader, line))
    {
        string str = line;
        result.push_back(str);
        counter++;
        line.clear();
    }
    return counter;
}

long GenerateConfigFont(const std::vector<std::string> strList, std::string tgtPath)
{
    if (strList.size() == 0) return -1;
    map<wchar_t, int> store;
    long counter = 0;

    for (string line : strList)
    {
        wstring wline;
        UTF82Unicode(line, wline);
        for (wchar_t c : wline)
        {
            if (store.find(c) == store.end())
            {
                store.insert(pair<wchar_t, int>(c, counter));
                counter++;
            }
        }
    }
    ofstream fileWriter;
    fileWriter.open(tgtPath);
    if (!fileWriter.is_open()) return -1;
    string tgt;
    fileWriter << YS_CONFIG_FONT_PREFIX;
    for (auto k : store)
    {
        const wstring wchar = { k.first };
        Unicode2UTF8(wchar, tgt);
        fileWriter << tgt <<endl;
    }
    fileWriter.close();
    return counter;
}
