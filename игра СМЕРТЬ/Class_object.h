#pragma once
#include "color.h"
#include "Class_item.h"
#include <iomanip>
#include <Windows.h>
#include <algorithm>

class Object
{
protected:
	bool passable; //можно ли встать на этот объект
	char sign;
	ConsoleColor text; // цвет текста
	ConsoleColor baground; //фон текста
public:
	bool object_prov(char** pole, int i_player, int g_player)//забей
	{
		return pole[i_player][g_player] == sign;
	}
	Object(char sign, ConsoleColor text, ConsoleColor baground, bool passable): sign{sign},  //конструктор
	text{text}, baground{baground}, passable{passable}
	{}
	Object()//забей
	{
		sign = ' ';
	}
	void print()//вывод с изменением цвета
	{
		SetColor(text, baground);
		std::cout << sign;
		SetColor(LightGray, Black);
	}
	
	bool get_passable()
	{
		return passable;
	}

	char get_sign()
	{
		return sign;
	}
	
};

class Living_Object: public Object
{
protected:
	int i;
	int g;
	int HP;
	int max_HP;
	int damage;
	int defence;
	Object* recent_object;//блок над которым стоит существо
	Living_Object(char sign, ConsoleColor text, ConsoleColor baground, int max_HP, int Damage, int Defence) : Object(sign, text, baground, false), i{ -1 }, g{ -1 }, HP{ max_HP }, 
	max_HP{ max_HP }, damage{Damage}, defence{Defence}
	{}
public:
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
};


class Player: public Living_Object
{
	int lighting_level;
	int raz_inventory;
	Item* inventory[10]; //[0]  - рука, туда можно поставить только определённые вещи
	
public:
	Player(char sign, ConsoleColor text, ConsoleColor baground, int max_HP, int Damage, int Defence) : Living_Object(sign, text, baground, max_HP, Damage, Defence),
		raz_inventory{ 10 }
	{
		lighting_level = 3;
		for (int i = 0; i < raz_inventory; i++)
		{
			inventory[i] = new Item;
		}
		inventory[1] = new Wooden_Sword;
		inventory[2] = new Health_Potion;
		inventory[3] = new Torch;
	}
	void work_inventory()
	{
		std::cout << "HP: " << HP << "\t\t" << "MAX_HP: " << max_HP << "\t\t" << "Damage: " << damage << "\t\t" << "Defence: " << defence << "\t\t" << "Уровеь освещения; " << lighting_level << "\n\n\n";
		std::cout << "Рука:" << std::right << std::setw(22) << inventory[0]->get_name() << std::right  << std::setw(22) << inventory[0]->get_description() << '\n';
		for (int i = 1; i < raz_inventory; i++)
		{

			std::cout << i << "\t\t\t\t" << inventory[i]->get_name() << "\t\t\t\t" << inventory[i]->get_description() << '\n';
		}
		std::cout << "\n\nЧто вы хотите сделать? 0 - поставить предмет в руку\n";
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
					for (int i = 1; i <= 9; ++i)
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
				}
				else
				{
					std::cout << "Этот предмет нельзя поместить в руку\n";
				}
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

};