#include <utility>
#include "Login.h"
#include "SendMsg.h"
#include "userInfo.h"
#include "chatroom.h"
#include "Sql.h"
#include "HelperService.h"
#include "common.h"
#include "json.h"

string HelperService::GetQRCode(http_message* http_message)
{
	return string();
}

string HelperService::GetLoginStatus(http_message* http_message)
{
	return string();
}

string HelperService::GetMyInfo(http_message* http_message)
{
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
	return "";
}

string HelperService::SendTextMsg(http_message* http_message)
{
	return string();
}

string HelperService::GetChatroomUser(http_message* http_message)
{
	return string();
}

string HelperService::Logout(http_message* http_message)
{
	if (isLogin()==0) {
		return "{code:-1200,msg:'ÄúÎ´µÇÂ¼'}";
	}
	return "{code:-1201,msg:'Î´ÊµÏÖ'}";
}
