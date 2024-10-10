#include "tool_config_font.h"
#include "ys_define.h"
#include <fstream>
#include <iostream>
#include <map>
#include "tool_charcode.h"

using namespace std;

long GenerateConfigFont(std::string poPath, std::string tgtPath)
{
    ifstream fileReader;
    fileReader.open(poPath);
    if (!fileReader.is_open()) return -1;
    string line;
    map<wchar_t, int> store;
    long counter = 0;

    while (getline(fileReader, line))
    {
        wstring wline;
        UTF82Unicode(line, wline);
        for (auto c : wline)
        {
            if (store.find(c) == store.end())
            {
                store.insert(pair<wchar_t, int>(c, counter));
                counter++;
            }
        }
        line.clear();
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
    fileReader.close();
    fileWriter.close();
}
