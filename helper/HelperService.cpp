#include <utility>
#include "Login.h"
#include "SendMsg.h"
#include "userInfo.h"
#include "chatroom.h"
#include "Sql.h"
#include "HelperService.h"
#include "common.h"
#include "offset.h"
#include "json/json.h"

string ok(string msg = "") {
	Json::Value root;
	root["code"] = 0;
	if (msg.empty()==false) {
		root["data"] = msg;
	}
	return root.toStyledString();
}

string error(int code=-1,string msg="") {
	Json::Value root;
	root["code"] = code;
	if (msg.empty() == false) {
		root["data"] = msg;
	}
	return root.toStyledString();
}

string HelperService::GetQRCode(http_message* http_message)
{
	if (isLogin() == 1) {
		return error(-1203, "ÄúÒÑµÇÂ¼");
	}
	GotoQrCode();
	Sleep(500);
	char qrcodeStr[500] = { 0 };
	sprintf_s(qrcodeStr, "http://weixin.qq.com/x/%s", (char*)*((DWORD*)(getWeChatWinAddr() + LOGINQRCODESTR)));
	return ok(qrcodeStr);
}

string HelperService::GetLoginStatus(http_message* http_message)
{
	string login = isLogin() == 0 ? "false" : "true";
	return ok(login);
}

string HelperService::GetMyInfo(http_message* http_message)
{
	if (isLogin() == 0) {
		return error(-1200, "ÄúÎ´µÇÂ¼");
	}
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
	return ok(data.toStyledString());
}
Json::Value contactList;
int getContactCallBackJson(void* para, int nColumn, char** colValue, char** colName)
{
	Json::Value row;
	for (int i = 0; i < nColumn; i++)
	{
		char data[1000] = { 0 };
		sprintf_s(data, "%s", colValue[i]);
		row[*(colName + i)] = string(data);
	}
	contactList.append(row);
	return 0;
}

string HelperService::GetContactInfo(http_message* http_message)
{
	if (isLogin() == 0) {
		return error(-1200, "ÄúÎ´µÇÂ¼");
	}
	char* sqlErrmsg = NULL;
	string sql = "select Contact.UserName,Contact.Alias,Contact.NickName,Contact.Remark,ContactHeadImgUrl.bigHeadImgUrl "
		" from Contact LEFT OUTER JOIN ContactHeadImgUrl ON Contact.UserName = ContactHeadImgUrl.usrName";
	runSql("MicroMsg.db", sql, getContactCallBackJson, sqlErrmsg);
	if (sqlErrmsg != NULL) {
		return error(-1230, sqlErrmsg);
	}
	
	string data = contactList.toStyledString();
	contactList.clear();
	return ok(data);
}

string HelperService::SendMsg(http_message* http_message)
{
	if (isLogin() == 0) {
		return error(-1200, "ÄúÎ´µÇÂ¼");
	}
	// ¼òµ¥postÇëÇó£¬¼Ó·¨ÔËËã²âÊÔ
	char wxid[200], msg[2000];
	mg_get_http_var(&http_message->body, "wxid", wxid, sizeof(wxid));
	mg_get_http_var(&http_message->body, "msg", msg, sizeof(msg));
	if (strlen(wxid) == 0) {
		return  error(-1210, "wxid ²»ÄÜÎª¿Õ");
	}
	if (strlen(msg) == 0) {
		return  error(-1211, "msg ²»ÄÜÎª¿Õ");
	}
	wchar_t* wxid_w = UTF8ToUnicode(wxid);
	wchar_t* msg_w = UTF8ToUnicode(msg);
	SendTextMsg(wxid_w, msg_w);
	return ok();
}

string HelperService::GetChatroomUser(http_message* http_message)
{
	if (isLogin() == 0) {
		return error(-1200, "ÄúÎ´µÇÂ¼");
	}
	return error(-1240, "ÄúÎ´µÇÂ¼");
}

string HelperService::Logout(http_message* http_message)
{
	if (isLogin() == 0) {
		return error(-1200, "ÄúÎ´µÇÂ¼");
	}
	LogoutWeChat();
	return ok();
}
