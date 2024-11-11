#pragma once
#include "ys_data_reader.h"
#include <string>
#include <vector>

long WriteVOs2CSV(std::vector<YS1ExeTVO> &yVOs, std::string tgtPath);

long WriteVOs2CSV(std::vector<ParaTranzVO> &ptVOs, std::string tgtPath);

long WriteVOs2PO(std::vector<YS1POVO> &poVOs, std::string tgtPath);

string FoldPOFormat(const std::string &poDataLine);