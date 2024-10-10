#include "csv_writer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

long WriteToCSV(std::string tgtPath, std::vector<std::string> &content)
{
    ofstream fileWriter;
    fileWriter.open(tgtPath);
    if (!fileWriter.is_open())
    {
        return -1;
    }
    long count = 0;
    string line;
    istringstream ss;
    for (int i = 0; i < content.size(); i++)
    {
        //one line as :  <ID>   <Text>  <Text>  <Text>  <Int>   <Int>   <Int>
        string col;
        ss.str(content[i] + "\t");
        while (getline(ss, col, '\t'))
        {
            //the first 
            if (all_of(col.begin(), col.end(), isdigit))
            {
                line += col;
            }
            //add double quotation marks around string
            else
            {
                line += "\"" + col + "\"";
            }
            line += ",";
        }
        count++;
        line += "\n";
        ss.clear();  //reset flag in istringstream
    }
    fileWriter << line;
    line.clear();
    fileWriter.close();
    return count;
}
