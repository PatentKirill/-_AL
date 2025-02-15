#pragma once

#include <string>
#include <iostream>

class Item
{
protected:
	std::string name;
public:
	Item(std::string name) : name{ "Пусто" }
	{

	}
	void print()
	{
		setlocale(LC_ALL, "RU");
		std::cout << name;
	}
	virtual void use()
	{}
};

class Healt_Potions
{
	void use(int i)
	{

	}
};
