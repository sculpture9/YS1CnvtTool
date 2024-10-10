// YS1TextTool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <iostream>
#include "csv_writer.h"
#include "ys1_exedata_reader.h"
#include "ys_define.h"
#include "tool_config_font.h"

int main()
{
    long result;
    //result = GenerateConfigFont(YS_SCANE_PO_PATH, YS_CONFIG_FONT_INI_PATH);
    vector<string> data = GetYS1O2ExeData(YS1_EXE_TEXT_PATH);
    long num = 0;
    if (data.size() != 0)
    {
        num = WriteToCSV(YS1_EXE_CSV_PATH, data);
    }
    else
    {
        data = GetYS1O2ExeData(YS2_EXE_TEXT_PATH);
        num = WriteToCSV(YS2_EXE_CSV_PATH, data);
    }
    cout << "Successfully converted " << num << "lines." << endl;
    getchar();
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
