#pragma once


#include <iostream>
#include <windows.h>
#include <string>


//������������ �����, ������ ������

class Item
{
protected:
	int ID;
	int meaning;
	std::string name;
	std::string description;
public:
	int get_ID()
	{
		return ID;
	}
	std::string get_name()
	{
		return name;
	}
	std::string get_description()
	{
		return description;
	}
	Item(std::string name, std::string description, int meaning, int ID) : name{ name }, description{ description }, meaning{ meaning }, ID{ ID }
	{

	}
	Item() : name{ "�������" }, description{ "��� ������ ���" }, meaning{ 0 }, ID{ 0 }
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
	Wooden_Sword() : Item("���������� ���", "������� ���", 6, 1)
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
	Burning_Sword() : Item("�������� ���", "�� �����", 15, 2)
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
	Torch() : Item("�����", "�������� ��� ����", 5, 3)
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
	Health_Potion() : Item("����� ��������", "��������������� 5 ��������", 5, 4)
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
	Potion_Life() : Item("����� �����", "������ ��� ����� �����(����������� ����. ��������)", 10, 5)
	{

	}
	virtual bool use(int& HP, int& max_HP, int& damage, int& defence, int& lighting_level)
	{
		max_HP += meaning;
		return true;
	}
};





//enum class num_Item
//{
//Potion
	//Potion_Life = 10,
	//Health_Potion = 11,
//������
    //Wooden_Sword = 20,

//Wooden_Sword
// };








