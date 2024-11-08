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

bool ReadDataFromPO(std::vector<std::vector<std::string>> &result, const LPCSTR &poPath, long &lineFlag);

bool ContainSubStr(std::string father, std::string son);