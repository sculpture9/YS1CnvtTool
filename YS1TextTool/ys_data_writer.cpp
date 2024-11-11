#include "ys_data_writer.h"
#include "ys_define.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

long WriteVOs2CSV(std::vector<YS1ExeTVO> &yVOs, std::string tgtPath)
{
    ofstream fileWriter;
    fileWriter.open(tgtPath);
    if (!fileWriter.is_open())
    {
        return -1;
    }
    long count = 0;
    string line;
    //istringstream ss;
    for (int i = 0; i < yVOs.size(); i++)
    {
        //one line as :  <ID>   <Text>  <Text>  <Text>  <Int>   <Int>   <Int>   <Int>
        YS1ExeTVO yvo = yVOs[i];
        string col;
        line += yvo.ID;
        line += ",";

        line += "\"" + yvo.OriginTxt + "\"";
        line += ",";

        line += "\"" + yvo.TranslatedTxt + "\"";
        line += ",";

        line += "\"" + yvo.FontStyle + "\"";
        line += ",";

        line += to_string(yvo.TSize);
        line += ",";

        line += to_string(yvo.CharSize);
        line += ",";

        line += to_string(yvo.AddressInYS1);
        line += ",";

        line += to_string(yvo.AddressByCaller);
        line += ",";

        //while (getline(ss, col, '\t'))
        //{
        //    //the first 
        //    if (all_of(col.begin(), col.end(), isdigit))
        //    {
        //        line += col;
        //    }
        //    //add double quotation marks around string
        //    else
        //    {
        //        line += "\"" + col + "\"";
        //    }
        //    line += ",";
        //}
        count++;
        line += "\n";
        //ss.clear();  //reset flag in istringstream
    }
    fileWriter << line;
    line.clear();
    fileWriter.close();
    return count;
}

long WriteVOs2CSV(std::vector<ParaTranzVO> &ptVOs, std::string tgtPath)
{
    ofstream fileWriter;
    fileWriter.open(tgtPath);
    if (!fileWriter.is_open())
    {
        fileWriter.close();
        return -1;
    }
    long count = 0;
    string line;
    for (int i = 0; i < ptVOs.size(); i++)
    {
        //one line as :  <ID>   <Text>  <Text>
        ParaTranzVO ptvo = ptVOs[i];
        string col;
        line += ptvo.Key;
        line += ",";

        line += "\"" + ptvo.Source + "\"";
        line += ",";

        line += "\"" + ptvo.Translation + "\"";
        line += ",";

        line += "\"" + ptvo.Context + "\"";
        line += ",";

        count++;
        line += "\n";
    }
    fileWriter << line;
    line.clear();
    fileWriter.close();
    return count;
}

long WriteVOs2PO(std::vector<YS1POVO> &poVOs, std::string tgtPath)
{
    ofstream fileWriter;
    fileWriter.open(tgtPath);
    if (!fileWriter.is_open())
    {
        fileWriter.close();
        return -1;
    }
    long count = 0;
    string line;
    //PO'Format: msgctxt "xxx"
    //           msgid ""
    //           "xxxxxxxxxx\n"
    //           "xxxxxxxxxx\n"
    //           "xxxxxxxxxx"
    //           msgstr ""
    //           "xxxxxxxxxx\n"
    //           "xxxxxxxxxx\n"
    //           "xxxxxxxxxx"
    fileWriter << YS1_SCANE_PO_PREFIX << endl;
    for (int i = 0; i < poVOs.size(); i++)
    {
        auto povo = poVOs[i];
        line += YS1_SCANE_PO_MSG_CTXT;
        line += "\"" + povo.msgctxt + "\"\n";
        line += YS1_SCANE_PO_MSG_ID;
        line += FoldPOFormat(povo.msgid);
        line += YS1_SCANE_PO_MSG_STR;
        line += FoldPOFormat(povo.msgstr);
        fileWriter << line << endl;
        line.clear();
        count++;
    }
    line.clear();
    fileWriter.close();
    return count;
}

string FoldPOFormat(const string &id_or_str)
{
    //one line
    if (id_or_str.find("\\n") == string::npos)
    {
        return "\"" + id_or_str + "\"\n";
    }

    //multilines
    string result;
    size_t strBegin = 0;
    bool escapeFlag = false;
    result += "\"\"\n";
    for (int i = 0; i < id_or_str.size(); i++)
    {
        auto c = id_or_str[i];
        
        if (!escapeFlag)
        {
            if (i == id_or_str.size() - 1)
            {
                result += "\"" + id_or_str.substr(strBegin, i - strBegin + 1) + "\"\n";
                break;
            }
            else if (c == '\\')
            {
                escapeFlag = true;
            }
            else if (c == '\0')
            {
                result += "\"" + id_or_str.substr(strBegin, i - strBegin) + "\"\n";
                strBegin = i;
            }
            else if (c == '\n')
            {
                result += "\"" + id_or_str.substr(strBegin, i - strBegin) + "\"";
                strBegin = i;
            }
        }
        else
        {
            if (c == 'n')
            {
                result += "\"" + id_or_str.substr(strBegin, i - strBegin + 1) + "\"\n";
                strBegin = i + 1;
                escapeFlag = false;
            }
            else
            {
                escapeFlag = false;
            }
        }
    }
    return result;
}