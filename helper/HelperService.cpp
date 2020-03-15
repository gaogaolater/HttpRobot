#include <utility>
#include "Login.h"
#include "SendMsg.h"
#include "userInfo.h"
#include "chatroom.h"
#include "Sql.h"
#include "HelperService.h"
#include "common.h"
#include "json.h"
#include "offset.h"

string HelperService::GetQRCode(http_message* http_message)
{
	if (isLogin() == 1) {
		return "{code:-1203,msg:'ÄúÒÑµÇÂ¼'}";
	}
	GotoQrCode();
	char qrcodeStr[500] = { 0 };
	sprintf_s(qrcodeStr, "http://weixin.qq.com/x/%s", (char*)*((DWORD*)(getWeChatWinAddr() + LOGINQRCODESTR)));
	return "{code:0,data:'"+ string(qrcodeStr) +"'}";
}

string HelperService::GetLoginStatus(http_message* http_message)
{
	string login = isLogin() == 0 ? "false" : "true";
	return "{code:0,data:"+ login +"}";
}

string HelperService::GetMyInfo(http_message* http_message)
{
	if (isLogin() == 0) {
		return "{code:-1200,msg:'ÄúÎ´µÇÂ¼'}";
	}
	Json::Value root;
	Json::Value data;
	Information* info = getMyInfo();
	data["account"] = UnicodeToUtf8(info->account);
	data["bigHeader"] = UnicodeToUtf8(info->bigHeader);
	data["city"] = UnicodeToUtf8(info->city);
	data["device"] = UnicodeToUtf8(info->device);
	data["email"] = UnicodeToUtf8(info->email);
	data["nation"] = UnicodeToUtf8(info->nation);
	data["nickname"] = UnicodeToUtf8(info->nickname);
	data["phone"] = UnicodeToUtf8(info->phone);
	data["province"] = UnicodeToUtf8(info->province);
	data["sex"] = info->sex;
	data["signName"] = UnicodeToUtf8(info->signName);
	data["wxid"] = UnicodeToUtf8(info->wxid);
	root["code"] = 0;
	root["data"] = data;
	return root.toStyledString();
}

INT getContactCallBackJson(void* para, int nColumn, char** colValue, char** colName)
{
	return 0;
}

string HelperService::GetContactInfo(http_message* http_message)
{
	if (isLogin() == 0) {
		return "{code:-1200,msg:'ÄúÎ´µÇÂ¼'}";
	}
	return "";
}

string HelperService::SendMsg(http_message* http_message)
{
	if (isLogin() == 0) {
		return "{code:-1200,msg:'ÄúÎ´µÇÂ¼'}";
	}
	// ¼òµ¥postÇëÇó£¬¼Ó·¨ÔËËã²âÊÔ
	char wxid[200], msg[2000];
	mg_get_http_var(&http_message->body, "wxid", wxid, sizeof(wxid));
	mg_get_http_var(&http_message->body, "msg", msg, sizeof(msg));
	if (strlen(wxid) == 0) {
		return  "{code:-1210,msg:'wxid ²»ÄÜÎª¿Õ'}";
	}
	if (strlen(msg) == 0) {
		return  "{code:-1211,msg:'msg ²»ÄÜÎª¿Õ'}";
	}
	wchar_t* wxid_w = UTF8ToUnicode(wxid);
	wchar_t* msg_w = UTF8ToUnicode(msg);
	SendTextMsg(wxid_w, msg_w);
	return "{code:0}";
}

string HelperService::GetChatroomUser(http_message* http_message)
{
	if (isLogin() == 0) {
		return "{code:-1200,msg:'ÄúÎ´µÇÂ¼'}";
	}
	return string();
}

string HelperService::Logout(http_message* http_message)
{
	if (isLogin() == 0) {
		return "{code:-1200,msg:'ÄúÎ´µÇÂ¼'}";
	}
	return "{code:-1201,msg:'Î´ÊµÏÖ'}";
}
