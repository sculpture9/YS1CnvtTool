#include "ys_data_reader.h"
#include "ys_define.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

std::vector<YS1ExeTVO> GetYS1ETVOs(const std::string &originalDataPath)
{
    vector<YS1ExeTVO> result;
    //We stipulate that data has 7 columns
    //id, origintxt, translatedTxt, styleFileName,tsize, charsize, address
    ifstream fileReader;
    fileReader.open(originalDataPath);
    if (!fileReader.is_open())
    {
        return result;
    }
    string line;
    long id = 0;
    while (getline(fileReader, line))
    {
        if (line.size() == 0) { continue; }
        YS1ExeTVO ys1Line;
        GetLineWithYS1Style(line, id, ys1Line);
        result.push_back(ys1Line);
        id++;
        line.clear();
    }
    return result;
}

std::vector<YS1ExeTVO> GetYS1ETVOs(const std::vector<std::vector<std::string>> &translatedCsv)
{
    if (translatedCsv.size() == 0 || translatedCsv[0].size() != YS1_EXE_TEXT_CSVCOL) { return {}; }
    vector<YS1ExeTVO> result;
    for (int i = 0; i < translatedCsv.size(); i++)
    {
        vector<string> colData = translatedCsv[i];
        YS1ExeTVO vo;
        //the translated csv format is : ID, OriginTxt, TranslatedTxt, fontStyle, tsize, charSize, address
        vo.ID = colData[0];
        vo.OriginTxt = colData[1];
        vo.TranslatedTxt = colData[2];
        vo.FontStyle = colData[3];
        vo.TSize = atoi(colData[4].c_str());
        vo.CharSize = atoi(colData[5].c_str());
        vo.AddressInYS1 = atoi(colData[6].c_str());
        result.push_back(vo);
    }
    return result;
}

std::vector<ParaTranzVO> GetPTVOs(const std::vector<std::vector<std::string>> &paraTranzCsv)
{
    if (paraTranzCsv.size() == 0 || paraTranzCsv[0].size() != YS1_EXE_TEXT_PARATRANZ_CSVCOL) { return {}; }
    vector<ParaTranzVO> result;
    for (int i = 0; i < paraTranzCsv.size(); i++)
    {
        vector<string> colData = paraTranzCsv[i];
        ParaTranzVO vo;
        //the ParaTranz csv format is : Key, Source, Translation, Context
        vo.Key = colData[0];
        vo.Source = colData[1];
        vo.Translation = colData[2];
        vo.Context = colData[3];
        result.push_back(vo);
    }
    return result;
}

std::vector<ParaTranzVO> GetPTVOs(const std::vector<YS1ExeTVO> &ys1ExeTVOs)
{
    if (ys1ExeTVOs.size() == 0) { return {}; }
    vector<ParaTranzVO> result;
    for (int i = 0; i < ys1ExeTVOs.size(); i++)
    {
        auto etvos = ys1ExeTVOs[i];
        ParaTranzVO vo;
        vo.Key = etvos.ID;
        vo.Source = etvos.OriginTxt;
        vo.Translation = etvos.TranslatedTxt;
        vo.Context = "";
        result.push_back(vo);
    }
    return result;
}

std::vector<ParaTranzVO> GetPTVOs(const std::vector<YS1POVO> &ys1POVOs) 
{
    if (ys1POVOs.size() == 0) { return {}; }
    vector<ParaTranzVO> result;
    for (int i = 0; i < ys1POVOs.size(); i++)
    {
        auto povo = ys1POVOs[i];
        ParaTranzVO ptvo;
        ptvo.Key = povo.msgctxt;
        ptvo.Source = MultiLine2One(povo.msgid, false);
        ptvo.Translation = MultiLine2One(povo.msgstr, false);
        result.push_back(ptvo);
    }
    return result;
}

std::vector<YS1POVO> GetYS1POVOs(const std::vector<std::vector<std::string>> &translatedPO)
{
    if (translatedPO.size() == 0 || translatedPO[0].size() != YS1_SCANE_POCOL) { return {}; }
    vector<YS1POVO> result;
    //PO'Format: msgctxt "xxx"
    //           msgid ""
    //           "xxxxxxxxxx\n"
    //           "xxxxxxxxxx\n"
    //           "xxxxxxxxxx"
    //           msgstr ""
    //           "xxxxxxxxxx\n"
    //           "xxxxxxxxxx\n"
    //           "xxxxxxxxxx"
    for (int i = 0; i < translatedPO.size(); i++)
    {
        auto temp = translatedPO[i];
        YS1POVO povo;
        povo.msgctxt = GetMsgctxtKey(temp[0]);
        povo.msgid = MultiLine2One(RemoveSubStr(temp[1], YS1_SCANE_PO_MSG_ID), false);
        povo.msgstr = MultiLine2One(RemoveSubStr(temp[2], YS1_SCANE_PO_MSG_STR), false);
        result.push_back(povo);
    }
    return result;
}

bool GetLineWithYS1Style(const string &oriLine, long id, YS1ExeTVO &ys1vo)
{
    if (oriLine.size() == 0) { return false; }
    //original line like this:
    //.rdata:004DBBE4	0000000D	C	Doctor Bludo
    //we don't need ".rdata:"
    int pos = oriLine.find_first_of(':');
    string ys1Line = oriLine.substr(pos + 1, oriLine.size());
    istringstream ss(ys1Line + '\t');
    string col;
    vector<string> temp;
    while (getline(ss, col, '\t'))
    {
        char *flag;
        long numCol = strtol(col.c_str(), &flag, 16);
        if (*flag == '\0')  //col is hex int
        {
            temp.push_back(to_string(numCol));
        }
        else  //col is english char
        {
            temp.push_back(col);
        }
        col.clear();
    }
    if (temp.size() != YS1O2_EXE_DATACOL) return false;
    //we need style like this: <id>    <orignalText>    <translatedText>  <stylePath>  <textSize>    <charSize>    <address> 
    ys1vo.ID = to_string(id);
    ys1vo.OriginTxt = temp[3];
    ys1vo.TranslatedTxt = " ";
    ys1vo.FontStyle = YS_FONT_STYLE_PSP;
    ys1vo.TSize = atoi(temp[1].c_str());
    ys1vo.CharSize = atoi(temp[2].c_str());
    ys1vo.AddressInYS1 = atoi(temp[0].c_str());
    ss.str("");
    ss.clear();
    return true;
}

string RemoveSubStr(string father, string son)
{
    size_t pos = father.find(son);
    if (pos != string::npos)
    {
        string fl = father.substr(0, pos);
        string fr = father.substr(pos + son.size(), father.size() - son.size() - pos);
        father = fl + fr;
        father = RemoveSubStr(father, son);
    }
    return father;
}

string GetMsgctxtKey(string line)
{
    line = RemoveSubStr(line, YS1_SCANE_PO_MSG_CTXT);
    line = RemoveSubStr(line, "\"");
    line = RemoveSubStr(line, "\n");
    return line;
}

string RemoveTwoSidesQM(string poLine)
{
    size_t pos = poLine.find_first_of('\"');
    if (pos == string::npos) { return poLine; }

    string left = poLine.substr(0, pos);
    string right = poLine.substr(pos + 1, poLine.size() - 1 - pos);

    pos = right.find_last_of('\"');
    if (pos == string::npos) { return poLine; }

    poLine = right.substr(0, pos);
    right = right.substr(pos + 1, right.size() - 1 - pos);

    poLine = left + poLine + right;
    return poLine;
}

string MultiLine2One(const string &ori, bool needQuotationMark)
{
    //original line: "xxxxxxxxxx\n"
    //               "xxxxxxxxxx\n"
    //               "xxxxxxxxxx"
    //taget line: xxxxxxxxxx\nxxxxxxxxxx\nxxxxxxxxxx
    if (ori.size() == 0) { return {}; }
    string result;
    string line;
    istringstream iss(ori);
    while (getline(iss, line))
    {
        result += RemoveTwoSidesQM(line);
        line.clear();
    }
    if (needQuotationMark)
    {
        result.insert(result.begin(), '\"');
        result += "\"";
    }
    iss.str("");
    iss.clear();
    return result;
}
