#include "ys1_exedata_reader.h"
#include "ys_define.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

std::vector<std::string> GetYS1O2ExeData(std::string dataPath)
{
    vector<string> result;
    //We stipulate that data has 6 columns
    //id, origintxt, translatedTxt, tsize, charsize, address
    ifstream fileReader;
    fileReader.open(dataPath);
    if (!fileReader.is_open())
    {
        return result;
    }
    string line;
    long id = 0;
    while (getline(fileReader, line))
    {
        if (line.size() == 0) { continue; }
        string ys1Line;
        LineCvt2YS1Style(line, id, ys1Line);
        result.push_back(ys1Line);
        id++;
        line.clear();
    }
    return result;
}

bool LineCvt2YS1Style(const string &oriLine, long id, string &ys1Line)
{
    if (oriLine.size() == 0) { return false; }
    //original line like this:
    //.rdata:004DBBE4	0000000D	C	Doctor Bludo
    //we don't need ".rdata:"
    int pos = oriLine.find_first_of(':');
    ys1Line = oriLine.substr(pos + 1, oriLine.size());
    istringstream ss(ys1Line + '\t');
    string col, result;
    vector<string> temp;
    while (getline(ss, col, '\t'))
    {
        char *flag;
        long numCol = strtol(col.c_str(), &flag, 16);
        if (*flag == '\0')  //col is hex int
        {
            temp.push_back(to_string(numCol));
        }
        else
        {
            temp.push_back(col);
        }
    }
    if (temp.size() != YS1O2_EXE_DATACOL) return false;
    //we need style like this: <id>    <orignalText>    <translatedText>  <stylePath>  <textSize>    <charSize>    <address> 
    result += to_string(id) + "\t";
    result += temp[3] + "\t";
    result += " \t";
    string yfsp(YS_FONT_STYLE_PSP);
    result += yfsp + "\t";
    //result += to_string(atoi(temp[1].c_str()) - 1) + "\t";  //minus one byte for '\0'
    result += temp[1] + "\t";
    result += temp[2] + "\t";
    result += temp[0];
    ys1Line = result;
    ss.str("");
    ss.clear();
    return true;
}
