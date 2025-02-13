#pragma once


class Object
{
protected:
	int i;
	int g;
	char sign;
public:
	bool object_prov(char** pole, int i_player, int g_player)
	{
		return pole[i_player][g_player] == sign;
	}
	Object(char sign)
	{
		this->sign = sign;
		i = -1;
		g = -1;
	}
	Object()
	{
		i = -1;
		g = -1;
		sign = ' ';
	}
	int get_i()
	{
		return i;
	}
	int get_g()
	{
		return g;
	}
	char get_sign()
	{
		return sign;
	}
	
};

class Wall: public Object
{
	
public:
	Wall(char sign) : Object(sign)
	{}
	void set_i_g(int i, int g)
	{
		this->i = i;
		this->g = g;
	}
	
};


class Player: public Object
{
public:
	Player(char sign) : Object(sign)
	{}
	Player() : Object()
	{}
	void set_player(int i, int g, char sign)
	{
		this->i = i;
		this->g = g;
		this->sign = sign;
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