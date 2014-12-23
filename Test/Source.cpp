#include"Windows.h"
#include<chrono>


int main()
{
	for (;;)
	{
		for (size_t i = 0; i < 1000000; i++);
		Sleep(10);
	}
}