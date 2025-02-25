#pragma once
//#include "Class_object.h"
#include "Class_item.h"
#include <map>

Object base{ ' ', LightGray, Black, true }; //базовый блок
Object wall{ '|', DarkGray, DarkGray, false };


std::map<char, Object> ID_object
{
	{base.get_sign(), base},
	{wall.get_sign(), wall}
};


