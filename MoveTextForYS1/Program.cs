using System;
using System.Collections.Generic;
using System.IO;
using ExcelDataReader;
namespace MoveTextForYS1
{
    internal struct Section
    {
        public int begin;
        public int end;
    }
    internal class Program
    {
        static string xlsxPath = "E:\\Project\\YSTranslationProject\\YS CHS\\text\\SC2ENGForSCENA.xlsx"; 
        static string originPOPath = "E:\\Project\\YSTranslationProject\\YS CHS\\text\\SCENA.po"; 
        static string tsPOPath = "E:\\Project\\YSTranslationProject\\YS CHS\\text\\SCENA 完全版简体中文[已勘正编码].po"; 
        static string targetPOPath = "E:\\Project\\YSTranslationProject\\YS CHS\\text\\SCENA Complete翻译移植版.po"; 
        static void Main(string[] args)
        {
            /*var node = NodeFactory.FromFile(targetPOPath);
            node.TransformWith(new Binary2Po()).Stream.WriteTo(target1POPath);*/
            //return;

            //获取行对应表
            var xlsxStream = File.Open(xlsxPath, FileMode.Open);
            var xlsxData = ExcelReaderFactory.CreateReader(xlsxStream);
            Console.WriteLine("Get Xlsx！");

            //获取PO数据
            var oriPO = File.ReadAllLines(originPOPath);
            var scPO = File.ReadAllLines(tsPOPath);
            Console.WriteLine("Get PO！");

            //获取行对应组
            GenerateSectionList(xlsxData, out var oriList, out var scList);
            xlsxData.Close();
            xlsxStream.Close();
            Console.WriteLine("PO Maped");

            //根据行对应组替换PO数据
            var result = GetResultOfTranslation(oriList, scList, oriPO, scPO);
            //保存结果
            if (result != null)
            {
                WritePO(result, targetPOPath);
                Console.WriteLine("Move Succeed！");
            }
            else Console.WriteLine("Move Failed！");

            Console.WriteLine("input any key to exit.");
            Console.ReadKey();
        }

        private static void GenerateSectionList(IExcelDataReader reader, out List<Section> oriList, out List<Section> scList)
        {
            //todo
            int oriBegin;
            oriList = new List<Section>();
            scList = new List<Section>();
            for(int i = 0; i < reader.RowCount; i++)
            {
                reader.Read();
                //表中只有四列数据
                int j = 0;
                string str = reader.GetValue(j).ToString();
                if(int.TryParse(str, out oriBegin))
                {
                    var oriSec = new Section();
                    var scSec = new Section();
                    oriSec.begin = oriBegin;
                    oriSec.end = int.Parse(reader.GetValue(j + 1).ToString());
                    scSec.begin = int.Parse(reader.GetValue(j + 2).ToString());
                    scSec.end = int.Parse(reader.GetValue(j + 3).ToString());
                    oriList.Add(oriSec);
                    scList.Add(scSec);
                }
            }
        }

        private enum TransStatus
        {
            DirectInput,
            Start,
            Done,
        }

        private static string[] GetResultOfTranslation(List<Section> oriList, List<Section> scList, string[] oriPO, string[] scPO)
        {
            if (oriList.Count != scList.Count) return null;

            List<string> result = new List<string>();
            int listCounter = 0;
            for (int i = 0; i < oriPO.Length; i++)
            {
                var oriStr = oriPO[i];
                //result.Add(oriStr);
                if (listCounter < oriList.Count && string.Equals(oriStr, $"msgctxt \"{oriList[listCounter].begin}\""))
                {
                    var transLineNo = TranslateSection(ref result, i, oriPO, scPO, oriList[listCounter], scList[listCounter]);
                    if (transLineNo != -1)
                    {
                        listCounter++;
                        i = transLineNo;
                    }
                    else return null;
                }
                else
                {
                    result.Add(oriStr + "\n");
                }
            } 
            return result.ToArray();
        }

        private static int TranslateSection(ref List<string> result, int oriLineNo, string[] oriPO, string[] scPO, Section oriSection, Section scSection)
        {
            if (oriSection.end - oriSection.begin != scSection.end - scSection.begin) return -1;  //翻译数据无法对齐则失败

            int curOriMsgctxt = oriSection.begin;
            int curScMsgctxt = scSection.begin;
            int cur = oriLineNo;
            TransStatus status = TransStatus.DirectInput;
            for (; curOriMsgctxt <= oriSection.end; cur++)
            {
                int count = cur;
                var oriStr = oriPO[cur];
                //以存在"msgctxt"的行，作为段的开始
                if (oriStr.Contains("msgctxt")) { status = TransStatus.DirectInput; }
                else if (oriStr.Contains("msgstr")) { status = TransStatus.Start; }

                switch (status)
                {
                    case TransStatus.DirectInput:
                        result.Add(oriStr + "\n");
                        break;
                    case TransStatus.Start:
                        Translate(ref result, scPO, curScMsgctxt);
                        curOriMsgctxt++;
                        curScMsgctxt++;
                        status = TransStatus.Done;
                        break;
                    case TransStatus.Done:
                        break;
                }
            }
            return cur;
        }

        private static int GetLineNumByMsgctext(string[] po, string msgctext)
        {
            for (int i = 0;i < po.Length;i++)
            {
                if(po[i].Contains(msgctext)) return i;
            }
            return -1;
        }

        private static void Translate(ref List<string> result, string[] scPO, int scMsgcTxt)
        {
            var tarMsg = $"msgctxt \"{scMsgcTxt}\"";
            bool isFound = false;
            int scLineNo = GetLineNumByMsgctext(scPO, $"msgctxt \"{scMsgcTxt}\"");
            for (int i = scLineNo; i < scPO.Length; i++)
            {
                var scStr = scPO[i];
                if (scStr.Contains(tarMsg)) 
                { 
                    isFound = true; 
                    continue;   //[msgctxt "<数字>"] 这行不需要输入，直接进入下一行，判断msgid的内容
                }
                if(!isFound) continue;

                //[msgstr ""] 表示本段已结束
                if (string.Equals(scStr, "msgstr \"\""))
                {
                    result.Add("\n");
                    isFound = false;
                    break;
                }
                //存在四种形式
                //1.msgid "<!empty>"
                //2.msgid ""
                //3.msgid "内容文本"
                //4."内容文本"
                if (string.Equals(scStr, "msgid \"<!empty>\"") || string.Equals(scStr, "msgid \"\""))
                {
                    result.Add("msgstr \"\"");
                }
                else if(scStr.Contains("msgid"))
                {
                    result.Add(scStr.Replace("msgid", "msgstr"));
                }
                else
                {
                    result.Add(scStr);
                }
                result.Add("\n");
            }
        }

        private static void WritePO(string[] content, string filePath)
        {
            var fs = File.CreateText(filePath);
            foreach (var line in content)
            {
                fs.Write(line);
                fs.Flush();
            }
            fs.Close();
        }
    }
}
