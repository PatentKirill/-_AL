
#include "Class_object.h"

#include "include.h"

Players player{ 2, 3, '@' };




class Total_pole
{
protected:
	
	Object wall{1, 1, '|'};
	Wall* mas_wall;
	
    int kol_wall;
	int current_wall;
	char** pole;
	int raz_i;
	int raz_g;
public:
	
	Total_pole(int rows, int columns, int kol_wall)
	{

		if (kol_wall < 1)
		{
			kol_wall = 1;
		}
		this->kol_wall = kol_wall;
		current_wall = 0;
		raz_i = rows;
		raz_g = columns;
		pole = new char* [rows];
		// выделяем память под двухмерный массив
		mas_wall = new Wall[kol_wall];
		for (int i = 0; i < rows; i++)
		{
			pole[i] = new char[columns];
		}


		for (int i = 0; i < raz_i; i++)
		{
			for (int g = 0; g < raz_g; g++)
			{
				pole[i][g] = '*';
			
			}
		}
		
		
	}
	~Total_pole()
	{

		for (int i = 0; i < raz_i; i++)
		{
			delete[] pole[i];
		}
		delete[] pole;
		delete[] mas_wall;
	}
	void print() 
	{
		
		system("cls");
		
		for (int i = 0; i < raz_i; i++)
		{
			for (int g = 0; g < raz_g; g++)
			{
				std::cout << pole[i][g];
			}
			std::cout << "\n";
		}
	}
	void prov_object() 
	{};
	void prov_wall()
	{
		for (int i = 0; i < raz_i; i++)
		{
			for (int g = 0; g < raz_g; g++)
			{
				for (int j = 0; j < this->kol_wall; j++)
				{
					if (i == mas_wall[j].get_i() && g == mas_wall[j].get_g())
					{
						pole[i][g] = '|';
					}
				}
			}
		}
	}
	void place_wall()
	{

	}
	void w()
	{
		if (
			(player.get_i() - 1) >= 0 &&
			pole[player.get_i() - 1][player.get_g()]  != mas_wall[0].get_sign()
			)
		{
			pole[player.get_i()][player.get_g()] = '*';
			player.w();
			pole[player.get_i()][player.get_g()] = player.get_sign();
			print();
		}
	}
	void s()
	{
		if (
			(player.get_i() + 1) < raz_i &&
			pole[player.get_i() + 1][player.get_g()] != mas_wall[0].get_sign()
			)
		{
			pole[player.get_i()][player.get_g()] = '*';
			player.s();
			pole[player.get_i()][player.get_g()] = player.get_sign();
			print();
		}
	}
	void a()
	{
		if (
			(player.get_g() - 1) >= 0 &&
			pole[player.get_i()][player.get_g() - 1] != mas_wall[0].get_sign()
			)
		{
			pole[player.get_i()][player.get_g()] = '*';
			player.a();
			pole[player.get_i()][player.get_g()] = player.get_sign();
			print();
		}
	}
	void d()
	{
		if (
			(player.get_g() + 1) < raz_g &&
			pole[player.get_i()][player.get_g() + 1] != mas_wall[0].get_sign()
			)
		{
			pole[player.get_i()][player.get_g()] = '*';
			player.d();
			pole[player.get_i()][player.get_g()] = player.get_sign();
			print();
		}
	}
};

class Start_pole: public Total_pole
{
	Object iii{ 0, 3, 'X' };
	void place_wall()
	{
		for (int i = 0; i < 5; i++)
		{
			
			mas_wall[i].set_i_g(i, i);
			current_wall++;
		}
		for (int i = current_wall; i < kol_wall; i++)
		{
			mas_wall[i].set_i_g(i, 9);
			current_wall++;
		}
	}
	
public:
	Start_pole(int rows, int columns, int kol_wall) :Total_pole(rows, columns, kol_wall)
	{
		
		
		place_wall();
		prov_wall();
		pole[9][5] = iii.get_sign();
	}
	void prov_x()
	{
		if (iii.get_i() == player.get_i() && iii.get_g() == player.get_g())
		{
			std::cout << "\n\nBUUUUU\n";
			Sleep(3000);
		}
	}
	
};

