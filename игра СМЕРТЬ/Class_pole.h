#pragma once
#include "Class_object.h"
#include "include.h"
#include <fstream>
#include <Windows.h>
//#include "ID_Object.h"




class Total_pole
{
protected:
	int raz_i; //размеры поля
	int raz_g;
	std::ifstream file;
	static Player player;//игрок
	Object*** pole;
public:
	Player& get_player()
	{
		return player;
	}
	Total_pole(std::string name_file) : raz_i{}, raz_g{}
	{
		file.open(name_file);
		if (file.is_open())
		{
			char sign;
			while (file.get(sign))
			{
				raz_g++;
				if (sign == '\n')
				{
					raz_i++;
					raz_g = 0;
				}
			}
			raz_i++;
			player.set_recent_object(&base);
			pole = new Object * *[raz_i];
			// выделяем память под двухмерный массив

			for (int i = 0; i < raz_i; i++)
			{
				pole[i] = new Object* [raz_g];
			}
			file.close();
			load(name_file, false);
		}
		else
		{
			std::cout << "Ошибка\n";
			file.close();
		}

		



	}

	void save(std::string name_file)
	{
		std::ofstream offile(name_file);
		player.save("player_save.txt");
		if (offile.is_open())
		{
			for (int i = 0; i < raz_i; i++)
			{
				for (int g = 0; g < raz_g; g++)
				{
					offile << pole[i][g]->get_sign();
				}
				offile << '\n';
			}
		}
		else
		{
			std::cout << "Ошибка save\n";
		}
		offile.close();
	}
	void load(std::string name_file, bool save_player)
	{


		file.open(name_file);
		if (save_player)
		{
			player.load("player_save.txt");
		}
		if (file.is_open())
		{
			char sign;
			for (int i = 0; i < raz_i; i++)//чтение из файла и запись в поле
			{
				for (int g = 0; g < raz_g; g++)
				{
					file.get(sign);
					if (sign == '\n')
					{
						g--;
					}
					else if (sign == player.get_sign())
					{
						pole[i][g] = &player;
						player.set_i_g(i, g);
					}
					else if (ID_object.find(sign) != ID_object.end())
					{
						pole[i][g] = &ID_object[sign];
					}
					else
					{
						pole[i][g] = &base;
					}
				}
			}
		}
	
		file.close();
	}
	void work_inventory()
	{
		
	
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