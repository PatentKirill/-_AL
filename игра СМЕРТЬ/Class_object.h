#pragma once
#include "color.h"

class Object
{
protected:
	bool passable;
	char sign;
	ConsoleColor text;
	ConsoleColor baground;
public:
	bool object_prov(char** pole, int i_player, int g_player)
	{
		return pole[i_player][g_player] == sign;
	}
	Object(char sign, ConsoleColor text, ConsoleColor baground, bool passable): sign{sign}, 
	text{text}, baground{baground}, passable{passable}
	{}
	Object()
	{
		sign = ' ';
	}
	void print()
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
	Object* recent_object;
	Living_Object(char sign, ConsoleColor text, ConsoleColor baground) : Object(sign, text, baground, false), i{ -1 }, g{ -1 }, HP{ 100 }
	{

	}
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
public:
	Player(char sign, ConsoleColor text, ConsoleColor baground) : Living_Object(sign, text, baground)
	{}
	

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