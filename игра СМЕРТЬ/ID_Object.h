#pragma once
//#include "Class_object.h"
//#include "Class_item.h"
#include <map>
//пробел не использовать, будут ошибки
Object base{ '1', Black, Black, true, false }; //базовый блок
Object wall{ '|', DarkGray, DarkGray, false, false };
Object grass{ 'l', LightGreen, Green, true, false };
Zmei zmei{ &base };


std::map<char, Object> ID_object
{
	{base.get_sign(), base},
	{wall.get_sign(), wall},
	{grass.get_sign(), grass},
};

std::map<char, Monster> ID_monster
{
	{zmei.get_sign(), zmei}

};




