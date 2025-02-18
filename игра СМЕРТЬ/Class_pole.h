#pragma once
#include "Class_object.h"
#include "include.h"
#include <fstream>
#include <Windows.h>





class Total_pole
{
protected:
	int raz_i; //размеры поля
	int raz_g;
	Object base; //базовый блок
	Object wall;
	std::ifstream file;
	Object*** pole;
	static Player player;//игрок

public:

	Total_pole(char* name_file): raz_i{},raz_g{}, base{' ', LightGray, Black, true}, wall{'|', DarkGray, DarkGray, false}
	{
		player.set_recent_object(&base);
		file.open(name_file);
		if (file.is_open())
		{
			char sign;
			file >> raz_i; //считывание разеров из файла
			file >> raz_g;
			
			Sleep(3000);
			pole = new Object** [raz_i];
			// выделяем память под двухмерный массив

			for (int i = 0; i < raz_i; i++)
			{
				pole[i] = new Object * [raz_g];
			}
			file.get(sign);
			while (sign != '\n')//ищем переход на новую строчку
			{
				file.get(sign);
			}
			for (int i = 0; i < raz_i; i++)//чтение из файла и запись в поле
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
						player.set_i_g(i, g);
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
			
		}
		else
		{
			std::cout << "Ошибка. Файл не удалось открыть\n";
		}



	}

	void work_inventory()
	{
		system("cls");
	
		player.work_inventory();
		print();
	}

	void print()//вывод
	{
		system("cls");
		for (int i = 0; i < raz_i; i++)
		{
			for (int g = 0; g < raz_g; g++)
			{
				if (
					player.get_i() + player.get_lighting_level() >= i && player.get_i() - player.get_lighting_level() <= i &&
					player.get_g() + player.get_lighting_level() >= g && player.get_g() - player.get_lighting_level() <= g
					)
				{
					pole[i][g]->print();
				}
				else
				{
					std::cout << ' ';
				}
			}
		    std::cout << "\n";
		}
	}
	void w()//для ходьбы
	{
		if (pole[player.get_i() - 1][player.get_g()]->get_passable())
		{
			pole[player.get_i()][player.get_g()] = player.get_recent_object();

			player.w();

			player.set_recent_object(pole[player.get_i()][player.get_g()]);

			pole[player.get_i()][player.get_g()] = &player;
			print();
		}

	}
	void s()
	{
		if (pole[player.get_i() + 1][player.get_g()]->get_passable())
		{
			pole[player.get_i()][player.get_g()] = player.get_recent_object();

			player.s();

			player.set_recent_object(pole[player.get_i()][player.get_g()]);

			pole[player.get_i()][player.get_g()] = &player;
			print();
		}

	}
	void d()
	{
		if (pole[player.get_i()][player.get_g() + 1]->get_passable())
		{
			pole[player.get_i()][player.get_g()] = player.get_recent_object();

			player.d();

			player.set_recent_object(pole[player.get_i()][player.get_g()]);

			pole[player.get_i()][player.get_g()] = &player;
			print();
		}

	}
	void a()
	{
		if (pole[player.get_i()][player.get_g() - 1]->get_passable())
		{
			pole[player.get_i()][player.get_g()] = player.get_recent_object();

			player.a();

			player.set_recent_object(pole[player.get_i()][player.get_g()]);

			pole[player.get_i()][player.get_g()] = &player;
			print();
		}

	}
};

Player Total_pole::player{ '@', Yellow, Black, 100, 10, 10 };