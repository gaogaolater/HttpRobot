#define _CRT_SECURE_NO_WARNINGS
#include "EasyLog.h"


EasyLog::EasyLog()
{
}


EasyLog::~EasyLog()
{
}

void EasyLog::Write(std::string log)
{
	try
	{
		std::ofstream ofs;
		time_t t = time(0);
		char tmp[64];
		strftime(tmp, sizeof(tmp), "[%Y-%m-%d %X]", localtime(&t));
		ofs.open("C:\\log\\PipeLog.txt", std::ofstream::app);
		ofs << tmp << " - ";
		ofs.write(log.c_str(), log.size());
		ofs << std::endl;
		ofs.close();
	}
	catch (...)
	{

	}
}
