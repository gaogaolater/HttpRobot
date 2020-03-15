#pragma once
#include <iostream>
#include "mongoose.h"
using namespace std;
class RobotService
{
public:
	static string CloseAllWx(http_message* http_message);
	static string StartWx(http_message* http_message);
};

