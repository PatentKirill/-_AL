#include "include.h"
#include "Class_pole.h"

#include <string>

std::string name_start_pole{ "default_start_pole.txt" };
std::string save_start_pole{ "save_start_pole.txt" };
Total_pole pole( name_start_pole );


//aaaaaaaaadffffdftyhgyhddffggsdfersdzaa


int main()
{
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	pole.print();
	

	//std::future<void> f_1 = std::async(control);
	int time{ 300 };
	while (1)
	{
		if (GetKeyState('W') & 0x8000)
		{
			pole.player_movement('w');
			Sleep(time);
		}
		else if (GetKeyState('S') & 0x8000)
		{
			pole.player_movement('s');
			Sleep(time);
		}
		else if (GetKeyState('A') & 0x8000)
		{
			pole.player_movement('a');
			Sleep(time);
		}
		else if (GetKeyState('D') & 0x8000)
		{
			pole.player_movement('d');
			Sleep(time);
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000)
		{
			pole.work_inventory();
			Sleep(time);
		}
		else if (GetKeyState('Q') & 0x8000)
		{
			pole.save(save_start_pole);
			Sleep(time);
		}
		else if (GetKeyState('E') & 0x8000)
		{
			pole.load(save_start_pole, true);
			pole.print();
			Sleep(time);
		}
		else
		{
			pole.monster_movent();
		}
	}
	
}


