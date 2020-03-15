#pragma once
#include <iostream>
#include "mongoose.h"
using namespace std;
class HelperService
{
public :
	static string GetQRCode(http_message* http_message);
	static string GetLoginStatus(http_message* http_message);
	static string GetMyInfo(http_message* http_message);
	static string GetContactInfo(http_message* http_message);
	static string SendMsg(http_message* http_message);
	static string GetChatroomUser(http_message* http_message);
	static string Logout(http_message* http_message);
};

