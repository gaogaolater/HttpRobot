#include <Windows.h>
#include <string>
#include <ctime>  
#include <iostream>  
#include <fstream>  
#include <direct.h>

DWORD getWeChatWinAddr();
VOID setGlobalHwnd(HWND hwnd);
HWND getGlobalHwnd();
char* UnicodeToUtf8(const wchar_t* unicode);
wchar_t* UTF8ToUnicode(const char* str);
std::string EncodeConvert(std::string sInfo, INT sourceEncode, INT targetEncode);
wchar_t* StrToWchar(std::string str);
void WriteLog(std::string log);