#include "RobotService.h"
#include <TlHelp32.h>
#include "resource.h"
#include "common.h"
string startWechatExe(wchar_t* weChatexe);

string RobotService::CloseAllWx(http_message* http_message) {
	HANDLE ProcesssAll = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 proessInfo = { 0 };
	proessInfo.dwSize = sizeof(PROCESSENTRY32);
	do
	{
		if (wcscmp(L"WeChat.exe", proessInfo.szExeFile) == 0) {
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, proessInfo.th32ProcessID);
			if (hProcess != NULL) {
				TerminateProcess(hProcess, 0);
			}
		}
	} while (Process32Next(ProcesssAll, &proessInfo));
	return "{code:0}";
}

string RobotService::StartWx(http_message* http_message) {
	//TODO::判断是否已经打开微信
	HKEY hKey;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Tencent\\WeChat", 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
	{
		return "{code:-1001,msg:'注册表打开失败'}";
	}
	TCHAR szProductType[MAX_PATH] = {};
	DWORD dwBufLen = MAX_PATH;
	if (RegQueryValueEx(hKey, L"InstallPath", NULL, NULL, (LPBYTE)szProductType, &dwBufLen) != ERROR_SUCCESS)
	{
		return "{code:-1002,msg:'注册表查询败'}";
	}
	RegCloseKey(hKey);
	wchar_t weChatexe[0x500] = { 0 };
	swprintf_s(weChatexe, L"%s\\WeChat.exe", (wchar_t*)szProductType);
	return startWechatExe(weChatexe);
}

string startWechatExe(wchar_t* weChatexe)
{
	wchar_t* path = new wchar_t(MAX_PATH);
	GetCurrentDirectory(MAX_PATH, path);
	string pathStr = UnicodeToUtf8(path);
	pathStr += "\\helper.dll";
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;//SW_SHOW
	CreateProcess(NULL, weChatexe, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
	LPVOID Param = VirtualAllocEx(pi.hProcess, NULL, MAX_PATH, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (Param == 0)
	{
		return "{code:1003,msg:'VirtualAllocEx失败'}";
	}
	WriteProcessMemory(pi.hProcess, Param, pathStr.c_str(), MAX_PATH, NULL);
	FARPROC address = GetProcAddress(GetModuleHandle(L"Kernel32.dll"), "LoadLibraryA");
	HANDLE hRemote = CreateRemoteThread(pi.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)address, Param, 0, NULL);
	ResumeThread(pi.hThread);
	return "{code:0}";
}