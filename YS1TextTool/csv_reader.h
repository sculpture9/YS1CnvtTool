#pragma once
#include "sstream"
#include "iostream"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<string>> ReadDataFromCSV(const string &csvPath);

bool CharVector2String(const vector<char> &chars, string &str);