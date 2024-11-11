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
    long AddressByCaller;
};

typedef struct YS1ExeAddonTVO
{
    string ID;
    string OriginTxtPrefix;
    long AddressByCaller;
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

std::vector<YS1ExeTVO> GetYS1ETVOs(const std::string &exeTextPath);

std::vector<YS1ExeTVO> GetYS1ETVOs(const std::vector<std::vector<std::string>> &translatedCsv);

std::vector<YS1ExeAddonTVO> GetYS1ATVOs(const std::string &exeAddonTextPath);

std::vector<ParaTranzVO> GetPTVOs(const std::vector<std::vector<std::string>> &paraTranzCsv);

std::vector<ParaTranzVO> GetPTVOs(const std::vector<YS1ExeTVO> &ys1ExeTVOs);

std::vector<ParaTranzVO> GetPTVOs(const std::vector<YS1POVO> &ys1POVOs, bool needEmpty = false);

std::vector<YS1POVO> GetYS1POVOs(const std::vector<std::vector<std::string>> &translatedPO);

bool ExeTLine2YS1ETVO(const std::string &exeTextLine, long id, YS1ExeTVO &ys1vo);

bool ExeAddonTLine2YS1ETVO(const std::string &exeTextLine, long id, YS1ExeAddonTVO &ys1vo);

std::string RemoveSubStr(std::string father, std::string son);

std::string GetMsgctxtKey(std::string line);

std::string RemoveTwoSidesQM(string poLine);

std::string MultiLine2One(const std::string &ori, bool needQuotationMark = true);