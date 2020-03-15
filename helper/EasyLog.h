#pragma once
#include <ctime>  
#include <iostream>  
#include <fstream>  
#include <direct.h>


using namespace std;

class EasyLog
{
public:
	EasyLog();
	~EasyLog();
	static void Write(std::string log);
};

