#pragma once
#include <string>
void SupportGetCSVFromExeText();
void SupportUpdateCSVWithAddonText(std::string oriCSVPath, std::string oriAddonTxtPath, std::string tgtCsvPath);
void GenerateConfigFontText();
void TransCSV2ParaTranzCSV();
void MergeParaTranzCSV2TransCSV();
void PO2ParaTranzCSV();
void MergeParaTranzCSV2PO();