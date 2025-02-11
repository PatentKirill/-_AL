#include "include.h"
#include "Class_pole.h"
#include <future>
#include <thread>


Start_pole pole{ 10, 10, 20};

//aaaaaaaaadffffdftyhgyhddffggsdf
void control()
{
	while (1)
	{
		if (GetKeyState('W') & 0x8000)
		{
			pole.w();
			Sleep(500);
		}
		else if (GetKeyState('S') & 0x8000)
		{
			pole.s();
			Sleep(500);
		}
		else if (GetKeyState('A') & 0x8000)
		{
			pole.a();
			Sleep(500);
		}
		else if (GetKeyState('D') & 0x8000)
		{
			pole.d();
			Sleep(500);
		}
	}
	
}

int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		(0 << 4) | 10);
	
	pole.print();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		(0 << 4) | 11);
	std::cout << "AAAA";
	std::future<void> f_1 = std::async(control);
}