
//f


class Object
{
protected:
	int i;
	int g;
	char sign;
public:
	Object(int i, int g, char sign)
	{
		this->i = i;
		this->g = g;
		this->sign = sign;
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
	Wall() : Object()
	{
		sign = '|';
	}
	void set_i_g(int i, int g)
	{
		this->i = i;
		this->g = g;
	}
	
};


class Players: public Object
{
public:
	Players(int x, int y, char sign) : Object(x, y, sign)
	{}
	Players() : Object()
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