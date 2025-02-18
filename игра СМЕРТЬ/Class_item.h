#pragma once

#include <string>
#include <iostream>
#include <windows.h>
//недоделанный класс, можешь забить

class Item
{
protected:
	int meaning;
	std::string name;
	std::string description;
public:
	std::string get_name()
	{
		return name;
	}
	std::string get_description()
	{
		return description;
	}
	Item(std::string name, std::string description, int meaning) : name{ name }, description{ description }, meaning{meaning}
	{

	}
	Item() : name{ "Пустота" }, description{ "Тут ничего нет" }, meaning{ 0 }
	{}
	void print()
	{
		setlocale(LC_ALL, "RU");
		std::cout << name;
	}
	virtual bool use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)
	{
		return false;
	}
	virtual bool active_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//для вещей которые можно держать в руке и для брони
	{
		return false;
	}
	virtual bool deactivate_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//для вещей которые можно держать в руке и для брони
	{
		return false;
	}
	virtual void useM(int& HP_M, int& max_HP_M, int& damageM, int& defenceM)
	{
	}
};

class Wooden_Sword: public Item
{
public:
	Wooden_Sword() : Item("Деревянный меч", "Обычный меч", 6)
	{}
	virtual bool active_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//для вещей которые можно держать в руке и для брони
	{
		damage += meaning;
		return true;
	}
	virtual bool deactivate_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//для вещей которые можно держать в руке и для брони
	{
		damage -= meaning;
		return true;
	}
};

class Burning_Sword : public Item
{
public:
	Burning_Sword() : Item("Огненный меч", "Он горит", 15)
	{}
	virtual bool active_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//для вещей которые можно держать в руке и для брони
	{
		damage += meaning;
		return true;
	}
	virtual bool deactivate_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//для вещей которые можно держать в руке и для брони
	{
		damage -= meaning;
		return true;
	}
};

class Torch: public Item
{
public:
	Torch() : Item("Факел", "Освещает вам путь", 5)
	{}
	virtual bool active_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//для вещей которые можно держать в руке и для брони
	{
		lighting_level += meaning;
		damage += meaning;
		return true;
	}
	virtual bool deactivate_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//для вещей которые можно держать в руке и для брони
	{
		lighting_level -= meaning;
		damage -= meaning;
		return true;
	}
};

class Health_Potion : public Item
{
public:
	Health_Potion() : Item("Зелье здоровья", "Восстонавливает 5 здоровья", 5)
	{
	}
	virtual bool use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)
	{
		HP += meaning;
		return true;
	}
};


class  Potion_Life : public Item
{
public:
	Potion_Life() : Item("Зелье жизни", "делает вас более живым(увеличивает макс. здоровье)", 10)
	{
	}
	virtual bool use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)
	{
		max_HP += meaning;
		return true;
	}
};







