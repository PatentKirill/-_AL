#pragma once


#include <iostream>
#include <windows.h>
#include <string>

//������������ �����, ������ ������

class Item
{
protected:
	std::string sign;
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
	Item(std::string name, std::string description, int meaning, std::string sign) : name{ name }, description{ description }, meaning{meaning}, sign{sign}
	{

	}
	Item() : name{ "�������" }, description{ "��� ������ ���" }, meaning{ 0 }, sign{' '}
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
	virtual bool active_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//��� ����� ������� ����� ������� � ���� � ��� �����
	{
		return false;
	}
	virtual bool deactivate_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//��� ����� ������� ����� ������� � ���� � ��� �����
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
	Wooden_Sword() : Item("���������� ���", "������� ���", 6, "W_S")
	{}
	virtual bool active_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//��� ����� ������� ����� ������� � ���� � ��� �����
	{
		damage += meaning;
		return true;
	}
	virtual bool deactivate_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//��� ����� ������� ����� ������� � ���� � ��� �����
	{
		damage -= meaning;
		return true;
	}
};

class Burning_Sword : public Item
{
public:
	Burning_Sword() : Item("�������� ���", "�� �����", 15, "B")
	{}
	virtual bool active_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//��� ����� ������� ����� ������� � ���� � ��� �����
	{
		damage += meaning;
		return true;
	}
	virtual bool deactivate_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//��� ����� ������� ����� ������� � ���� � ��� �����
	{
		damage -= meaning;
		return true;
	}
};

class Torch: public Item
{
public:
	Torch() : Item("�����", "�������� ��� ����", 5, "T")
	{}
	virtual bool active_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//��� ����� ������� ����� ������� � ���� � ��� �����
	{
		lighting_level += meaning;
		damage += meaning;
		return true;
	}
	virtual bool deactivate_use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)//��� ����� ������� ����� ������� � ���� � ��� �����
	{
		lighting_level -= meaning;
		damage -= meaning;
		return true;
	}
};

class Health_Potion : public Item
{
public:
	Health_Potion() : Item("����� ��������", "��������������� 5 ��������", 5, "H_P")
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
	Potion_Life() : Item("����� �����", "������ ��� ����� �����(����������� ����. ��������)", 10, "P_L")
	{
	std:to_string(item);
	}
	virtual bool use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)
	{
		max_HP += meaning;
		return true;
	}
};

Item item;
Potion_Life  potion_life;
Health_Potion health_potion;
Wooden_Sword wooden_Sword;



//enum class num_Item
//{
//Potion
	//Potion_Life = 10,
	//Health_Potion = 11,
//������
    //Wooden_Sword = 20,

//Wooden_Sword
// };








