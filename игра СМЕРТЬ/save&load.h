#pragma once
#include <fstream>
#include <iostream>
#include "Class_pole.h"


void save()
{
	Player players{}
	std::ofstream save("save.txt", std::ios::app);
	if (save.is_open())
	{
		save >> 
	}
	else
	{
		std::cout << "Ошибка открытия файла сохранения\n";
	}
}