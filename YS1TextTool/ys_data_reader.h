#pragma once
#include <fstream>
#include <string>
#include <vector>
using namespace std;

typedef struct YS1ExeTVO
{
    string ID;
    string OriginTxt;
    string TranslatedTxt;
    string FontStyle;
    long TSize;
    long CharSize;
    long AddressInYS1;
};

typedef struct ParaTranzVO
{
    string Key;
    string Source;
    string Translation;
    string Context;
};

typedef struct YS1POVO
{
    std::string msgctxt;
    std::string msgid;
    std::string msgstr;
};

std::vector<YS1ExeTVO> GetYS1ETVOs(const std::string &originalDataPath);

std::vector<YS1ExeTVO> GetYS1ETVOs(const std::vector<std::vector<std::string>> &translatedCsv);

std::vector<ParaTranzVO> GetPTVOs(const std::vector<std::vector<std::string>> &paraTranzCsv);

std::vector<ParaTranzVO> GetPTVOs(const std::vector<YS1ExeTVO> &ys1ExeTVOs);

std::vector<ParaTranzVO> GetPTVOs(const std::vector<YS1POVO> &ys1POVOs);

std::vector<YS1POVO> GetYS1POVOs(const std::vector<std::vector<std::string>> &translatedPO);

bool GetLineWithYS1Style(const std::string &oriLine, long id, YS1ExeTVO &ys1vo);

std::string RemoveSubStr(std::string father, std::string son);

std::string GetMsgctxtKey(std::string line);

std::string RemoveTwoSidesQM(string poLine);

std::string MultiLine2One(const std::string &ori, bool needQuotationMark = true);