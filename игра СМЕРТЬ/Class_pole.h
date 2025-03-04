#pragma once
#include "Class_object.h"
#include "include.h"
#include <fstream>
#include <Windows.h>
#include <ctime>
#include <vector>
//#include "ID_Object.h"




class Total_pole
{
protected:
	int raz_i; //размеры пол€
	int raz_g;
	std::ifstream file;
	static Player player;//игрок
	std::vector<Monster*> mas_mons;
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
			// выдел€ем пам€ть под двухмерный массив

			for (int i = 0; i < raz_i; i++)
			{
				pole[i] = new Object* [raz_g];
			}
			file.close();
			load(name_file, false);
		}
		else
		{
			std::cout << "ќшибка\n";
			Sleep(30000);
			file.close();
		}

		



	}
	~Total_pole()
	{
		for (int i = 0; i < raz_i; i++)
		{
			delete[] pole[i];
		}
		delete[] pole;
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
			std::cout << "ќшибка save\n";
		}
		offile.close();
	}
	void load(std::string name_file, bool save_player)
	{


		file.open(name_file);
		for (int i = 0; i < mas_mons.size(); i++)
		{
			mas_mons.pop_back();
		}
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

					else if (ID_monster.find(sign) != ID_monster.end())
					{
						pole[i][g] = &ID_monster[sign];


						mas_mons.push_back(&ID_monster[sign]);
						mas_mons.back()->set_i_g(i, g);
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
		
	
		player.work_inventory(false);
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

	void player_movement(char where)
	{
		if (where == 'w')
		{
			w(&player, -1);
		}
		else if (where == 's')
		{
			s(&player, -1);
		}
		else if (where == 'a')
		{
			a(&player, -1);
		}
		else if (where == 'd')
		{
			d(&player, -1);
		}
	}

	void monster_movent()
	{
		srand(time(NULL));
		if (!mas_mons.empty())
		{
			int num = 1 + rand() % mas_mons.size();
			num--;
			int where = 1 + rand() % 4;
			if (where == 1)
			{
				w(mas_mons[num], num);
			}
			else if (where == 2)
			{
				s(mas_mons[num], num);
			}
			else if (where == 3)
			{
				d(mas_mons[num], num);
			}
			else if (where == 4)
			{
				a(mas_mons[num], num);
			}
		}
		
	}

	void w(Living_Object* entity, int num)
	{
		if (pole[entity->get_i() - 1][entity->get_g()]->get_fight())
		{
			if (num == -1)// -1 значит что передалс€ игрок, если передалось любое другое значение это €чейка mas_mons
			{
				for (num = 0; !mas_mons[num]->prov_i_g(entity->get_i() - 1, entity->get_g()); num++ )
				{}
				player.fight(mas_mons[num], &player);
			}
			else if (pole[entity->get_i() - 1][entity->get_g()] == &player)//провер€ем, наткнулс€ ли монстр на игрока(чтобы монстр с монстром не начали дратьс€)
			{
				mas_mons[num]->fight(mas_mons[num], &player);
			}
		}
		else if (pole[entity->get_i() - 1][entity->get_g()]->get_passable())
		{
			pole[entity->get_i()][entity->get_g()] = entity->get_recent_object();

			entity->w();

			entity->set_recent_object(pole[entity->get_i()][entity->get_g()]);

			pole[entity->get_i()][entity->get_g()] = entity;
			print();
		}

	}

	void s(Living_Object* entity, int num)
	{
		if (pole[entity->get_i() + 1][entity->get_g()]->get_passable())
		{
			pole[entity->get_i()][entity->get_g()] = entity->get_recent_object();

			entity->s();

			entity->set_recent_object(pole[entity->get_i()][entity->get_g()]);

			pole[entity->get_i()][entity->get_g()] = entity;
			print();
		}

	}

	void d(Living_Object* entity, int num)
	{
		if (pole[entity->get_i()][entity->get_g() + 1]->get_passable())
		{
			pole[entity->get_i()][entity->get_g()] = entity->get_recent_object();

			entity->d();

			entity->set_recent_object(pole[entity->get_i()][entity->get_g()]);

			pole[entity->get_i()][entity->get_g()] = entity;
			print();
		}

	}
	void a(Living_Object* entity, int num)
	{
		if (pole[entity->get_i()][entity->get_g() - 1]->get_passable())
		{
			pole[entity->get_i()][entity->get_g()] = entity->get_recent_object();

			entity->a();

			entity->set_recent_object(pole[entity->get_i()][entity->get_g()]);

			pole[entity->get_i()][entity->get_g()] = entity;
			print();
		}

	}
};

Player Total_pole::player{ '@', Yellow, Black, 100, 10, 10 };