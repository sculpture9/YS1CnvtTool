#pragma once
#include<string>
#include<vector>
#include <Windows.h>

enum ReadPoStatus
{
    Idle,
    ReadTxt,
    ReadId,
    ReadStr,
};

bool ReadDataFromPO(std::vector<std::vector<std::string>> &result, const std::string &poPath, long &lineFlag);

bool ContainSubStr(std::string father, std::string son);