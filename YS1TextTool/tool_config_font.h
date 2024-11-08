#pragma once
#include <string>
#include <vector>

long GetStrList(std::string path, std::vector<std::string> &result);

long GenerateConfigFont(const std::vector<std::string> strList, std::string tgtPath);