#pragma once

#include <string>
#include <iostream>
#include <windows.h>
//недоделанный класс, можешь забить

class Item
{
protected:
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
	Item(std::string name, std::string description) : name{ name }, description{ description }
	{

	}
	Item() : name{ "Пустота" }, description{ "Тут ничего нет" }
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
	virtual bool active_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//для вещей которые можно держать в руке и для брони
	{
		damage += 10;
		return true;
	}
	virtual bool deactivate_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//для вещей которые можно держать в руке и для брони
	{
		damage -= 10;
		return true;
	}
};

class Health_Potion : public Item
{
public:
	Health_Potion() : Item("Зелье здоровья", "Восстонавливает 5 здоровья")
	{
	}
	virtual bool use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)
	{
		HP += 5;
		return true;
	}
};





