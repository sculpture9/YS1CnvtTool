#pragma once
#include <string>
typedef struct Section
{
    int begin;
    int end;
};

void SupportGetExeCSV();
void SupportUpdateExeCSV(std::string tgtCsvPath, std::string oriCSVPath, std::string oriAddonTxtPath);
void GenerateConfigFontText();
void TransCSV2ParaTranzCSV();
void MergeEXEParaTranzCSV2EXECSV();
void PO2ParaTranzCSV();
void SupportUpdatePOCSVWithPO(std::string tgtCsvPath, std::string sectionCSVPath, std::string oriCSVPath, std::string addonPOPath);
void MergeParaTranzCSV2PO();
void GenerateSectionList(std::vector<std::vector<std::string>> matchCSV, std::vector<Section> &oriList, std::vector<Section> &scList);
std::vector<YS1POVO> GetResultOfTranslation(std::vector<Section> oriSecList, std::vector<Section> scSecList, std::vector<YS1POVO> oriPOVOs, std::vector<YS1POVO> scPOVOs);
int TranslateSection(std::vector<YS1POVO> &result, int oriLineNo, const std::vector<YS1POVO> &oriPO, const std::vector<YS1POVO> &scPO, Section oriSection, Section scSection);
void MatchPOText(std::string tgtPOPath, std::string sectionCSVPath, std::string oriPOPath, std::string scPOPath);
void DividedParaTranzCSV(int fileCapacity);
void MergeParaTranzCSV(int fileNum);