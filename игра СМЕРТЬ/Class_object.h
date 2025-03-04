#pragma once
#include "color.h"
#include "Class_item.h"
#include <iomanip>
#include <Windows.h>
#include <algorithm>
#include <conio.h>
//#include "ID_Object.h" // ошибка из-за этой строчки
#include "ID_Item.h"

#include <fstream>


class Object
{
protected:
	bool passable; //можно ли встать на этот объект
	char sign;
	bool fight;
	ConsoleColor text; // цвет текста
	ConsoleColor baground; //фон текста
public:
	bool object_prov(char** pole, int i_player, int g_player)//забей
	{
		return pole[i_player][g_player] == sign;
	}
	Object(char sign, ConsoleColor text, ConsoleColor baground, bool passable, bool fight): sign{sign},  //конструктор
	text{text}, baground{baground}, passable{passable}, fight{fight}
	{}
	Object()//забей
	{
	
	}
	void print()//вывод с изменением цвета
	{
		SetColor(text, baground);
		std::cout << sign;
		SetColor(LightGray, Black);
	}
	
	bool get_fight()
	{
		return fight;
	}

	bool get_passable()
	{
		return passable;
	}

	char get_sign()
	{
		return sign;
	}
	// далее чисто виртуальные методы для класса Monster
	virtual ~Object()
	{

	}
	
	

};


class Monster;
class Player;

class Living_Object : public Object
{
protected:
	int i;
	int g;
	int HP;
	int max_HP;
	int damage;
	int defence;
	Object* recent_object;//блок над которым стоит существо
	std::string name;
	Living_Object(char sign, ConsoleColor text, ConsoleColor baground, bool fight, int max_HP, int Damage, int Defence, Object* recent_object, std::string name) : Object(sign, text, baground, false, fight), i{ -1 }, g{ -1 }, HP{ max_HP },
	max_HP{ max_HP }, damage{ Damage }, defence{ Defence }, recent_object{ recent_object }, name{name}
	{}
public:
	Living_Object() : Object()
	{
	}
	virtual ~Living_Object()
	{
	}
	void set_i_g(int i, int g)
	{
		this->i = i;
		this->g = g;
	}
	int get_i()
	{
		return i;
	}
	int get_g()
	{
		return g;
	}
	void set_recent_object(Object* object)
	{
		recent_object = object;
	}
	Object* get_recent_object()
	{
		return recent_object;
	}
	void w()
	{
		i--;
	}
	void s()
	{
		i++;
	}
	void a()
	{
		g--;
	}
	void d()
	{
		g++;
	}


	void fight(Monster* enemy, Player* player);
	void fight_print(Monster* enemy, Player* player);
	

	void attack(Living_Object* enemy, std::string name)
	{
		srand(time(NULL));
		if (enemy)
		{
			int prom_damage{ damage };
			int kol_defence = 1 + rand() % enemy->defence;
			prom_damage -= kol_defence;
			std::cout << name << " защитился на " << kol_defence << "\n";
			_getch();
			std::cout << name << " получил урон на " << prom_damage << "\n";
			_getch();
		}
	}
};

#include "Class_Monster.h"

#include "ID_Object.h" //должно быть перед Player

class Player: public Living_Object
{
	int lighting_level;
	int raz_inventory;
	Item* inventory[10]; //[0]  - рука, туда можно поставить только определённые вещи
	
public:
	Player(char sign, ConsoleColor text, ConsoleColor baground, int max_HP, int Damage, int Defence) : Living_Object(sign, text, baground, max_HP, Damage, Defence, true, &base, "Ты"),
		raz_inventory{ 10 }
	{
		lighting_level = 3;
		for (int i = 0; i < raz_inventory; i++)
		{
			inventory[i] = new Item;
		}
		
	}
	void save(std::string name_file)
	{
		std::ofstream file(name_file);
		if (file.is_open())
		{
			file << max_HP << " " << HP << " " << damage << " " << defence << " " << lighting_level << " " << recent_object->get_sign() << '\n';
			for (int i = 0; i < raz_inventory; i++)
			{
				file << inventory[i]->get_ID() << ' ';
			}
		}
		else
		{
			std::cout << "Ошибка save\n";
		}
	}
	void print_player()
	{
		std::cout << name << ":\n" << "HP:  " << max_HP << '/' << HP << "\tDamage:  " << damage << "\tDefence:  " << defence << '\n';
	}

	void load(std::string name_file)
	{
		std::ifstream file(name_file);
		if (file.is_open())
		{
			char prom;
			file >> max_HP >> HP >> damage >> defence >> lighting_level >> prom;
			recent_object = &ID_object[prom];
			for (int i = 0, ID = 0; i < raz_inventory; i++)
			{
				file >> ID;
				inventory[i] = &ID_item[ID];
			}
		}
		else
		{
			std::cout << "Ошибка load\n";
		}
	}
	void print_inventory()
	{
		system("cls");
		std::cout << "HP: " << HP << "\t\t" << "MAX_HP: " << max_HP << "\t\t" << "Damage: " << damage << "\t\t" << "Defence: " << defence << "\t\t" << "Уровеь освещения; " << lighting_level << "\n\n\n";
		std::cout << "Рука:" << std::right << std::setw(22) << inventory[0]->get_name() << std::right << std::setw(22) << inventory[0]->get_description() << '\n';
		for (int i = 1; i < raz_inventory; i++)
		{

			std::cout << i << "\t\t\t\t" << inventory[i]->get_name() << "\t\t\t\t" << inventory[i]->get_description() << '\n';
		}
		std::cout << "\n\nЧто вы хотите сделать? 0 - поставить предмет в руку; U - использовать предмет\n";
	}
	void work_inventory(bool one)
	{
		print_inventory();

		bool prov{true};
		Sleep(1000);
		while (prov == true)
		{
			
			if (GetKeyState('0') & 0x8000)
			{
				std::cout << "Введите номер предмета который хотите поместить в руку\n";
				inventory[0]->deactivate_use(HP, max_HP, damage, defence, lighting_level);
				int num{-1};
				while (num == -1)
				{
					for (int i = 1; i < raz_inventory; ++i)
					{
						if (GetKeyState('0' + i) & 0x8000)
						{
							num = i;
							
							break;
						}
						
					}
				}
				if (inventory[num]->active_use(HP, max_HP, damage, defence, lighting_level))
				{
					std::swap(inventory[num], inventory[0]);
					if (one)
					{
						return;
					}
				}
				else
				{
					std::cout << "Этот предмет нельзя поместить в руку\n";
				}
				print_inventory();
				Sleep(300);
			}
			
			if (GetKeyState('U') & 0x8000)
			{


				std::cout << "Введите номер предмета который хотите использовать\n";
				inventory[0]->deactivate_use(HP, max_HP, damage, defence, lighting_level);
				int num{ -1 };
				while (num == -1)
				{
					for (int i = 0; i <= 9; ++i)
					{
						if (GetKeyState('0' + i) & 0x8000)
						{
							num = i;

							break;
						}

					}
				}
				if (inventory[num]->use(HP, max_HP, damage, defence, lighting_level))
				{
					std::cout << "Предмет использован\n";
					inventory[num] = &item;
					if (one)
					{
						return;
					}
				}
				else
				{
					std::cout << "Этот предмет нельзя использовать\n";
				}
				print_inventory();
				Sleep(300);
			}

			else if (GetKeyState(VK_ESCAPE) & 0x8000)
			{
	
				prov = false;
				
			}
		}
		
		
	}
	


	int get_lighting_level()
	{
		return lighting_level;
	}

	

};

void Living_Object::fight_print(Monster* enem, Player* playe)
{
	system("cls");
	playe->print_player();
	enem->print_Monster();
}

void Living_Object::fight(Monster* enemy, Player* player)
{
	fight_print(enemy, player);
	std::cout << "Что вы хотите сделать?\n";
	while (_getch() != '\r') {}
}








