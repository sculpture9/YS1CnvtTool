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
    //MatchPOText(TARGET_PO_PATH, SC2ENGFORSCENA_PATH, ORIGIN_PO_PATH, TS_PO_PATH);
    //SupportGetCSVFromExeText();
    //SupportUpdateCSVWithAddonText(YS1_EXE_CSV_TGT_PATH, YS1_EXE_CSV_ORI_PATH, YS1_EXE_ADDON_TEXT_ORI_PATH);
    //SupportUpdateCSVWithAddonText(YS2_EXE_CSV_TGT_PATH, YS2_EXE_CSV_ORI_PATH, YS2_EXE_ADDON_TEXT_ORI_PATH);
    GenerateConfigFontText();
    //TransCSV2ParaTranzCSV();
    //PO2ParaTranzCSV();
    //SupportUpdatePOCSVWithPO(YS1_SCANE_CSV_PT_TGT_PATH, ENGBaseOnJPN4SCENA_PATH, YS1_SCANE_CSV_PT_ORI_PATH, JPN_PO_ORI_PATH);
    //DividedParaTranzCSV(100);
    //MergeParaTranzCSV(20);
    //MergeParaTranzCSV2PO();
    //MergeEXEParaTranzCSV2EXECSV();
    cout << "succeed! press any key to exit." << endl;
    _getch();
}

void SupportGetExeCSV()
{
    vector<YS1ExeTVO> data = GetYS1ETVOs(YS1_EXE_TEXT_ORI_PATH);
    long num = 0;
    if (data.size() != 0)
    {
        num = WriteVOs2CSV(data, YS1_EXE_CSV_ORI_PATH);
    }
    else
    {
        data = GetYS1ETVOs(YS2_EXE_TEXT_ORI_PATH);
        num = WriteVOs2CSV(data, YS2_EXE_CSV_ORI_PATH);
    }
    cout << "Successfully converted " << num << "lines." << endl;
}

void SupportUpdateExeCSV(std::string tgtCsvPath, std::string oriCSVPath, std::string oriAddonTxtPath)
{
    vector<vector<string>> exeData;
    vector<vector<string>> exeAddonData;
    long lflag = 0;
    bool bRet = ReadDataFromCSV(exeData, oriCSVPath, lflag, false);
    vector<YS1ExeTVO> result = GetYS1ETVOs(exeData);
    vector<YS1ExeAddonTVO> ysaddVOs = GetYS1ATVOs(oriAddonTxtPath);
    for (int i = 0; i < ysaddVOs.size(); i++)
    {
        for (int j = 0; j < result.size(); j++)
        {
            int pos = result[j].OriginTxt.find(ysaddVOs[i].OriginTxtPrefix);
            if (pos != string::npos)
            {
                result[j].AddressByCaller = ysaddVOs[i].AddressByCaller;
                break;
            }
        }
    }
    WriteVOs2CSV(result, tgtCsvPath);
}


void GenerateConfigFontText()
{
    long result;
    vector<string> strList;
    GetStrList(YS1_SCANE_PO_ORI_PATH, strList);
    GetStrList(YS1_EXE_CSV_ORI_PATH, strList);
    result = GenerateConfigFont(strList, YS_CONFIG_FONT_INI_PATH);
    cout << "Successfully Generate Config Font " << result << " pieces." << endl;
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

void MergeEXEParaTranzCSV2EXECSV()
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
    WriteVOs2CSV(tgtETVOs, YS1_EXE_CSV_TGT_PATH);
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

void SupportUpdatePOCSVWithPO(std::string tgtCsvPath, std::string sectionCSVPath, std::string oriCSVPath, std::string addonPOPath)
{
    vector<vector<string>> oriCSV;
    vector<vector<string>> addonPO;
    vector<vector<string>> sectionCSV;
    long readNum;
    ReadDataFromCSV(oriCSV, oriCSVPath, readNum, false);
    ReadDataFromPO(addonPO, addonPOPath, readNum);

    ReadDataFromCSV(sectionCSV, sectionCSVPath, readNum);
    vector<Section> oriList;
    vector<Section> scList;
    GenerateSectionList(sectionCSV, oriList, scList);

    vector<ParaTranzVO> ptVOs = GetPTVOs(oriCSV, true);
    vector<YS1POVO> addonPOVOs = GetYS1POVOs(addonPO);
    int secCounter = 0;
    for (int i = 0; i < ptVOs.size(); i++)
    {
        if (secCounter >= oriList.size()) { break; } 
        int ptvosKey = atoi(ptVOs[i].Key.c_str());
        if (ptvosKey < oriList[secCounter].begin) { continue; }

        if ((oriList[secCounter].end - oriList[secCounter].begin) != (scList[secCounter].end - scList[secCounter].begin))
        {
            cout << "The two csv data no equal." << endl;
            return;
        }
        int offset = scList[secCounter].begin - oriList[secCounter].begin;
        for (int j = 0; j < addonPOVOs.size(); j++)
        {
            if (ptvosKey + offset == atoi(addonPOVOs[j].msgctxt.c_str()))
            {
                ptVOs[i].Context = addonPOVOs[j].msgid;
                addonPOVOs.erase(addonPOVOs.begin() + j);
            }
        }
        if (ptvosKey == oriList[secCounter].end)
        {
            secCounter++;
        }
    }
    WriteVOs2CSV(ptVOs, tgtCsvPath);
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
                //ptVOs.erase(ptVOs.begin() + j);
                break;
            }
            //if no found
            if (j == ptVOs.size() - 1)
            {
                cout << YS1_SCANE_PO_MSG_CTXT << ": " << tgtVOs[i].msgctxt << " Not Repalce. " << endl;
                cout << YS1_SCANE_PO_MSG_ID << ": " << tgtVOs[i].msgid << endl;
            }
        }
    }
    WriteVOs2PO(tgtVOs, YS1_SCANE_PO_TGT_PATH);
}

void MatchPOText(std::string tgtPOPath, std::string sectionCSVPath, std::string oriPOPath, std::string scPOPath)
{
    /*var node = NodeFactory.FromFile(targetPOPath);
node.TransformWith(new Binary2Po()).Stream.WriteTo(target1POPath);*/
//return;

    //获取行对应表
    vector<vector<string>> matchCsv;
    long lineFlag;
    ReadDataFromCSV(matchCsv, sectionCSVPath, lineFlag);
    cout <<("Get CSV！") << endl;

    //获取PO数据
    vector<vector<string>> oriPOCSV;
    vector<vector<string>> scPOCSV;
    ReadDataFromPO(oriPOCSV, oriPOPath, lineFlag);
    ReadDataFromPO(scPOCSV, scPOPath, lineFlag);
    vector<YS1POVO> oriPO = GetYS1POVOs(oriPOCSV);
    vector<YS1POVO> scPOPO = GetYS1POVOs(scPOCSV);
    cout << ("Get PO！") << endl;

    //获取行对应组
    vector<Section> oriList;
    vector<Section> scList;
    GenerateSectionList(matchCsv, oriList, scList);
    cout << ("PO Maped") << endl;

    //根据行对应组替换PO数据
    vector<YS1POVO> result = GetResultOfTranslation(oriList, scList, oriPO, scPOPO);
    //保存结果
    if (result.size() != 0)
    {
        WriteVOs2PO(result, tgtPOPath);
        cout << ("Move Succeed！") << endl;
    }
    else cout << ("Move Failed！") << endl;
}

void DividedParaTranzCSV(int fileCapacity)
{
    if (fileCapacity <= 0) { return; }
    vector<vector<string>> ptCSV;
    long lineFLag;
    ReadDataFromCSV(ptCSV, YS1_SCANE_CSV_PT_ORI_PATH, lineFLag, false);
    vector<ParaTranzVO> ptVOs = GetPTVOs(ptCSV);
    vector<ParaTranzVO> writeData;
    int counter = 0;
    int flag = 0;
    for (int i = 0; i < ptVOs.size(); i++)
    {
        counter++;
        if ((counter % fileCapacity) == 0 || i == (ptVOs.size() - 1))
        {
            flag++;
            writeData.push_back(ptVOs[i]);
            WriteVOs2CSV(writeData, YS1_SCANE_CSV_PT_DIVIDED_TGT_PATH_PREFIX + to_string(flag) + ".csv");
            writeData.clear();
        }
        else
        {
            writeData.push_back(ptVOs[i]);
        }
    }
}

void MergeParaTranzCSV(int fileNum)
{
    if (fileNum <= 1) { return; }
    vector<ParaTranzVO> result;
    vector<vector<string>> sonCSV;
    vector<ParaTranzVO> sonVOs; 
    long lineFLag;
    for (int flag = 1; flag <= fileNum; flag++)
    {
        ReadDataFromCSV(sonCSV, YS1_SCANE_CSV_PT_DIVIDED_ORI_PATH_PREFIX + to_string(flag) + ".csv", lineFLag, false);
        sonVOs = GetPTVOs(sonCSV);
        for (int i = 0; i < sonVOs.size(); i++)
        {
            result.push_back(sonVOs[i]);
        }
        sonCSV.clear();
        sonVOs.clear();
    }
    WriteVOs2CSV(result, YS1_SCANE_CSV_PT_TGT_PATH);
}

void GenerateSectionList(vector<vector<string>> matchCSV, vector<Section> &oriList, vector<Section> &scList)
{
    for (int i = 0; i < matchCSV.size(); i++)
    {
        //表中只有四列数据
        auto line = matchCSV[i];
        Section oriSec;
        Section scSec;
        oriSec.begin = atoi(line[0].c_str());
        oriSec.end = atoi(line[1].c_str());
        scSec.begin = atoi(line[2].c_str());
        scSec.end = atoi(line[3].c_str());
        oriList.push_back(oriSec);
        scList.push_back(scSec);
    }
}

vector<YS1POVO> GetResultOfTranslation(vector<Section> oriSecList, vector<Section> scSecList, vector<YS1POVO> oriPOVOs, vector<YS1POVO> scPOVOs)
{
    if (oriSecList.size() != scSecList.size()) return {};

    vector<YS1POVO> result;
    int secCounter = 0;
    for (int i = 0; i < oriPOVOs.size(); i++)
    {
        if (secCounter < oriSecList.size() && atoi(oriPOVOs[i].msgctxt.c_str()) == oriSecList[secCounter].begin)
        {
            int oriPOVOCounter = TranslateSection(result, i, oriPOVOs, scPOVOs, oriSecList[secCounter], scSecList[secCounter]);
            if (oriPOVOCounter != -1)
            {
                secCounter++;
                i = oriPOVOCounter;
            }
            else return {};
        }
        else
        {
            result.push_back(oriPOVOs[i]);
        }
    }
    return result;
}

int TranslateSection(vector<YS1POVO> &result, int oriLineNo, const vector<YS1POVO> &oriPO, const vector<YS1POVO> &scPO, Section oriSection, Section scSection)
{
    if (oriSection.end - oriSection.begin != scSection.end - scSection.begin) return -1;  //翻译数据无法对齐则失败

    int oriCounter = oriSection.begin;
    int scCounter = scSection.begin;
   
    for (; oriCounter <= oriSection.end; oriCounter++, scCounter++)
    {
        auto poTemp = oriPO[oriCounter];
        poTemp.msgstr = scPO[scCounter].msgid;
        result.push_back(poTemp);
        
    }
    int povoCounter = oriCounter - 1;  //return current counter
    return povoCounter;
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
