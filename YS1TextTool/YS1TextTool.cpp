// YS1TextTool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <iostream>
#include "ys_data_writer.h"
#include "ys_data_reader.h"
#include "ys_define.h"
#include "tool_config_font.h"
#include "YS1TextTool.h"
#include "conio.h"
#include "csv_reader.h"
#include "po_reader.h"

int main()
{
    //GetCSVFromExeText();
    //GenerateConfigFontText();
    //TransCSV2ParaTranzCSV();
    //PO2ParaTranzCSV();
    MergeParaTranzCSV2PO();

    cout << "press any key to exit." << endl;
    _getch();
}

void GetCSVFromExeText()
{
    vector<YS1ExeTVO> data = GetYS1ETVOs(YS1_EXE_TEXT_ORI_PATH);
    long num = 0;
    if (data.size() != 0)
    {
        num = WriteVOs2CSV(data, YS1_EXE_CSV_ORI_PATH);
    }
    else
    {
        data = GetYS1ETVOs(YS2_EXE_TEXT_PATH);
        num = WriteVOs2CSV(data, YS2_EXE_CSV_PATH);
    }
    cout << "Successfully converted " << num << "lines." << endl;
}

void GenerateConfigFontText()
{
    long result;
    vector<string> strList;
    GetStrList(YS1_SCANE_PO_ORI_PATH, strList);
    GetStrList(YS1_EXE_CSV_ORI_PATH, strList);
    result = GenerateConfigFont(strList, YS_CONFIG_FONT_INI_PATH);
    cout << "Successfully Generate Config Font " << result << "pieces." << endl;
}

void TransCSV2ParaTranzCSV()
{
    vector<vector<string>> exeData;
    long lflag;
    bool bRet = ReadDataFromCSV(exeData, YS1_EXE_CSV_ORI_PATH, lflag, false);
    if (!bRet) { return; }
    vector<YS1ExeTVO> ysetvos = GetYS1ETVOs(exeData);
    if (ysetvos.size() == 0) return;
    vector<ParaTranzVO> ptvos = GetPTVOs(ysetvos);
    WriteVOs2CSV(ptvos, YS1_EXE_CSV_PT_TGT_PATH);
}

void MergeParaTranzCSV2TransCSV()
{
    vector<vector<string>> exeData;
    vector<vector<string>> ptData;
    long eflag;
    long pflag;
    ReadDataFromCSV(exeData, YS1_EXE_CSV_ORI_PATH, eflag, false);
    ReadDataFromCSV(ptData, YS1_EXE_CSV_PT_ORI_PATH, pflag, false);
    vector<YS1ExeTVO> tgtETVOs = GetYS1ETVOs(exeData);
    vector<ParaTranzVO> ptVOs = GetPTVOs(ptData);
    if (tgtETVOs.size() != ptVOs.size())
    {
        cout << "两表文本数量不同，请核对" << endl;
        return;
    }

    for (int i = 0; i < tgtETVOs.size(); i++)
    {
        for (int j = 0; j < ptVOs.size(); j++)
        {
            ParaTranzVO ptVO = ptVOs[j];
            if (strcmp(ptVO.Key.c_str(), tgtETVOs[i].ID.c_str()) == 0)
            {
                tgtETVOs[i].TranslatedTxt = ptVO.Translation;
                ptVOs.erase(ptVOs.begin() + j);
                break;
            }
        }
    }
    WriteVOs2CSV(tgtETVOs, YS1_EXE_CSV_ORI_PATH);
}

void PO2ParaTranzCSV()
{
    vector<vector<string>> data;
    long readNum;
    bool bRet = ReadDataFromPO(data, YS1_SCANE_PO_ORI_PATH, readNum);
    if (!bRet) { return; }
    vector<YS1POVO> poVOs = GetYS1POVOs(data);
    vector<ParaTranzVO> ptVOs = GetPTVOs(poVOs);
    WriteVOs2CSV(ptVOs, YS1_SCANE_CSV_PT_TGT_PATH);
}

void MergeParaTranzCSV2PO()
{
    vector<vector<string>> csvData;
    vector<vector<string>> poData;
    long readNum;
    ReadDataFromCSV(csvData, YS1_SCANE_CSV_PT_ORI_PATH, readNum, false);
    ReadDataFromPO(poData, YS1_SCANE_PO_ORI_PATH, readNum);
    vector<ParaTranzVO> ptVOs = GetPTVOs(csvData);
    vector<YS1POVO> tgtVOs = GetYS1POVOs(poData);
    for (int i = 0; i < tgtVOs.size(); i++)
    {
        for (int j = 0; j < ptVOs.size(); j++)
        {
            ParaTranzVO ptVO = ptVOs[j];
            if (strcmp(ptVO.Key.c_str(), tgtVOs[i].msgctxt.c_str()) == 0)
            {
                tgtVOs[i].msgstr = ptVO.Translation;
                ptVOs.erase(ptVOs.begin() + j);
                break;
            }
        }
    }
    WriteVOs2CSV(tgtVOs, YS1_SCANE_PO_TGT_PATH);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
