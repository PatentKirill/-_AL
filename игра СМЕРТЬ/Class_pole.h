#pragma once
#include "Class_object.h"
#include "include.h"
#include <fstream>

Player player{ '@' };




class Total_pole
{
protected:
	int raz_i;
	int raz_g;
	Object base{ '*' };
	Wall wall{ '|' };
	std::ifstream file;
	Object*** pole;
public:

	Total_pole(char* name_file)
	{
		file.open(name_file);
		if (file.is_open())
		{
			char sign;
			file >> raz_i;
			file >> raz_g;
			
			Sleep(3000);
			pole = new Object * *[raz_i];
			// выделяем память под двухмерный массив

			for (int i = 0; i < raz_i; i++)
			{
				pole[i] = new Object * [raz_g];
			}
			file.get(sign);
			while (sign != '\n')
			{
				file.get(sign);
			}
			for (int i = 0; i < raz_i; i++)
			{
				for (int g = 0; g < raz_g; g++)
				{
					file.get(sign);
					if (sign == base.get_sign())
					{
						pole[i][g] = &base;
					}
					else if (sign == wall.get_sign())
					{
						pole[i][g] = &wall;
					}
					else if (sign == player.get_sign())
					{
						pole[i][g] = &player;
					}
					else if (sign == '\n')
					{
						g--;
					}
					else
					{
						pole[i][g] = &base;
					}
				}
			}
			while (file.get(sign))
			{
				
			}
		}
		else
		{
			std::cout << "Ошибка. Файл не удалось открыть\n";
		}



	}

	void print()
	{
		for (int i = 0; i < raz_i; i++)
		{
			for (int g = 0; g < raz_g; g++)
			{
				std::cout << pole[i][g]->get_sign();
			}
		    std::cout << "\n";
		}
	}
};