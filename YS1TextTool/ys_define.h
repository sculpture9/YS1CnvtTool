#pragma once
//与C#不同，C++相对路径在工程目录底下

constexpr auto ENGBaseOnSC4SCENA_PATH = "work\\source\\ENGBaseOnSC4SCENA.csv";

constexpr auto ENGBaseOnJPN4SCENA_PATH = "work\\source\\ENGBaseOnJPN4SCENA.csv";

constexpr auto ORI_PO_ORI_PATH = "work\\source\\SCENA.po";

constexpr auto JPN_PO_ORI_PATH = "work\\source\\SCENA_Chronicle_JPN.po";

constexpr auto TS_PO_ORI_PATH = "work\\source\\SCENA 完全版简体中文[已勘正编码].po";

constexpr auto TARGET_PO_PATH = "work\\target\\SCENA Complete翻译移植版.po";

constexpr auto YS1_TRANSLATED_PATH = "text\\";

constexpr auto YS1_EXE_TEXT_ORI_PATH = "work\\source\\ys1_exe_text.txt";

constexpr auto YS1_EXE_ADDON_TEXT_ORI_PATH = "work\\source\\ys1_exe_addon_text.txt";

constexpr auto YS1_EXE_CSV_ORI_PATH = "work\\source\\ys1_exe_text.csv";

constexpr auto YS1_EXE_CSV_TGT_PATH = "work\\target\\ys1_exe_text.csv";

constexpr auto YS1_EXE_CSV_PT_ORI_PATH = "work\\source\\ys1_exe_pt_text.csv";

constexpr auto YS1_EXE_CSV_PT_TGT_PATH = "work\\target\\ys1_exe_pt_text.csv";

constexpr auto YS2_EXE_TEXT_ORI_PATH = "work\\source\\ys2_exe_text.txt";

constexpr auto YS2_EXE_ADDON_TEXT_ORI_PATH = "work\\source\\ys2_exe_addon_text.txt";

constexpr auto YS2_EXE_CSV_ORI_PATH = "work\\source\\ys2_exe_text.csv";

constexpr auto YS2_EXE_CSV_TGT_PATH = "work\\target\\ys2_exe_text.csv";

constexpr auto YS1O2_EXE_DATACOL = 4;

constexpr auto YS1_EXE_TEXT_CSVCOL = 8;

constexpr auto YS1_EXE_TEXT_PARATRANZ_CSVCOL = 4;

constexpr auto YS1_EXE_TEXT_PARATRANZ_COM_CSVCOL = 3;

constexpr auto YS1_SCANE_POCOL = 3;

constexpr auto YS_FONT_STYLE_DIA = "text2.ini";

constexpr auto YS_FONT_STYLE_PSP = "text.ini";

constexpr auto YS1_SCANE_PO_ORI_PATH = "work\\source\\SCENA Complete翻译移植版.po";

constexpr auto YS1_SCANE_CSV_PT_ORI_PATH = "work\\source\\SCENA_pt.csv";

constexpr auto YS1_SCANE_CSV_PT_DIVIDED_ORI_PATH_PREFIX = "work\\source\\divided_pt_csv\\SCENA_pt_part";

constexpr auto YS1_SCANE_PO_TGT_PATH = "work\\target\\SCENA Complete翻译移植版.po";

constexpr auto YS1_SCANE_CSV_PT_TGT_PATH = "work\\target\\SCENA_pt.csv";

constexpr auto YS1_SCANE_CSV_PT_DIVIDED_TGT_PATH_PREFIX = "work\\target\\divided_pt_csv\\SCENA_pt_part";

constexpr auto YS_CONFIG_FONT_INI_PATH = "work\\target\\config_font.ini";

constexpr auto YS_CONFIG_FONT_PREFIX = "CharacterSize=18\nMaxHeightFromOrigin=8\nFont=fonts/msyh.ttf\nSpaceWidth=8";

constexpr auto YS1_SCANE_PO_MSG_CTXT = "msgctxt ";

constexpr auto YS1_SCANE_PO_MSG_ID = "msgid ";

constexpr auto YS1_SCANE_PO_MSG_STR = "msgstr ";

constexpr auto YS1_SCANE_PO_MSG_ID_EMPTY = "<!empty>";

constexpr auto YS1_SCANE_PO_PREFIX = "msgid \"\"\nmsgstr \"\"\n\"Project-Id-Version: Ys I & II Chronicles+\\n\"\n\"Report-Msgid-Bugs-To: anyemail@gmail.com\\n\"\n\"POT-Creation-Date: 2024/11/3\\n\"\n\"PO-Revision-Date: \\n\"\n\"Last-Translator: \\n\"\n\"Language-Team: Any\\n\"\n\"Language: zh-CN\\n\"\n\"MIME-Version: 1.0\\n\"\n\"Content-Type: text/plain; charset=UTF-8\\n\"\n\"Content-Transfer-Encoding: 8bit\\n\"\n";