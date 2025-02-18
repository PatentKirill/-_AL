#include "include.h"
#include "Class_pole.h"

char name[100]{ "file.txt" };
Total_pole pole( name );

//aaaaaaaaadffffdftyhgyhddffggsdfersdzaa
void control()
{
	int time{ 300 };
	while (true)
	{
		if (GetKeyState('W') & 0x8000)
		{
			pole.w();
			Sleep(time);
		}
		else if (GetKeyState('S') & 0x8000)
		{
			pole.s();
			Sleep(time);
		}
		else if (GetKeyState('A') & 0x8000)
		{
			pole.a();
			Sleep(time);
		}
		else if (GetKeyState('D') & 0x8000)
		{
			pole.d();
			Sleep(time);
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000)
		{
			pole.work_inventory();
			Sleep(time);
		}
		
	}
	
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	pole.print();
	
	std::future<void> f_1 = std::async(control);
}


