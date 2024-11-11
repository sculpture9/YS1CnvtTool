#pragma once
#include <string>
typedef struct Section
{
    int begin;
    int end;
};

void SupportGetCSVFromExeText();
void SupportUpdateCSVWithAddonText(std::string oriCSVPath, std::string oriAddonTxtPath, std::string tgtCsvPath);
void GenerateConfigFontText();
void TransCSV2ParaTranzCSV();
void MergeParaTranzCSV2TransCSV();
void PO2ParaTranzCSV();
void MergeParaTranzCSV2PO();
void GenerateSectionList(std::vector<std::vector<std::string>> matchCSV, std::vector<Section> &oriList, std::vector<Section> &scList);
std::vector<YS1POVO> GetResultOfTranslation(std::vector<Section> oriSecList, std::vector<Section> scSecList, std::vector<YS1POVO> oriPOVOs, std::vector<YS1POVO> scPOVOs);
int TranslateSection(std::vector<YS1POVO> &result, int oriLineNo, const std::vector<YS1POVO> &oriPO, const std::vector<YS1POVO> &scPO, Section oriSection, Section scSection);
void MatchPOText(std::string tgtPOPath, std::string matchCSVPath, std::string oriPOPath, std::string scPOPath);