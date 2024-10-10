#pragma once
#include <fstream>
#include <string>
#include <vector>
using namespace std;
std::vector<std::string> GetYS1O2ExeData(std::string dataPath);

bool LineCvt2YS1Style(const string &oriLine, long id, string &ys1Line);