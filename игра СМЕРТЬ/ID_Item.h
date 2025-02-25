#pragma once
#include "Class_item.h"
#include <map>

Item item;
Potion_Life potion_life;
Health_Potion health_potion;
Wooden_Sword wooden_sword;
Burning_Sword burning_sword;
Torch torch;

std::map<int, Item> ID_item
{
	{ item.get_ID(), item},
	{ wooden_sword.get_ID(), wooden_sword },
	{ burning_sword.get_ID(), burning_sword },
	{ health_potion.get_ID(), health_potion },
	{potion_life.get_ID(), potion_life},
	{torch.get_ID(), torch}

};