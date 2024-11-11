#include "po_reader.h"
#include "ys_define.h"
#include <fstream>
#include <iostream>

using namespace std;

bool ReadDataFromPO(std::vector<std::vector<std::string>> &result, const std::string &poPath, long &lineFlag)
{
    ifstream reader;
    reader.open(poPath);
    if (!reader.is_open())
    {
        reader.close();
        return false;
    }

    string line;
    ReadPoStatus status = Idle;
    vector<string> wTemp;
    while (getline(reader, line))
    {
        switch (status)
        {
            //PO'Format: msgctxt "xxx"
            //           msgid ""
            //           "xxxxxxxxxx\n"
            //           "xxxxxxxxxx\n"
            //           "xxxxxxxxxx"
            //           msgstr ""
            //           "xxxxxxxxxx\n"
            //           "xxxxxxxxxx\n"
            //           "xxxxxxxxxx"
            case Idle:
                if (ContainSubStr(line, YS1_SCANE_PO_MSG_CTXT))   
                {
                    status = ReadTxt;
                    wTemp.push_back(line + "\n");
                }
                break;
            case ReadTxt:
                if (ContainSubStr(line, YS1_SCANE_PO_MSG_ID)) 
                { 
                    status = ReadId;
                    wTemp.push_back(line + "\n");
                }
                else
                {
                    cout << "msgctxt \"" << wTemp[0]<< "\", format is wrong!!!";
                }
                break;
            case ReadId:
                if (ContainSubStr(line, YS1_SCANE_PO_MSG_STR)) 
                { 
                    status = ReadStr;
                    wTemp.push_back(line + "\n");
                }
                else
                {
                    //removeSubStr(line, YS_SCANE_PO_MSG_ID);
                    wTemp.back() += (line + "\n");
                }
                break;
            case ReadStr:
                if (strcmp(line.c_str(), "\n") == 0 || strcmp(line.c_str(), "") == 0)
                {
                    vector<string> wRet = wTemp;
                    result.push_back(wRet);
                    lineFlag++;
                    wTemp.clear();
                    status = Idle;
                }
                else if (ContainSubStr(line, YS1_SCANE_PO_MSG_CTXT))
                {
                    vector<string> wRet = wTemp;
                    result.push_back(wRet);
                    lineFlag++;
                    wTemp.clear();
                    status = ReadTxt;
                    wTemp.push_back(line + "\n");
                }
                else
                {
                    //removeSubStr(line, YS_SCANE_PO_MSG_STR);
                    wTemp.back() += (line + "\n");
                }
                break;
        }
    }
    //add the last data
    vector<string> wRet = wTemp;
    result.push_back(wRet);
    reader.close();
    return true;
}

bool ContainSubStr(string father, string son)
{
    size_t pos = father.find(son);
    return pos != string::npos;
}
