#include <stdio.h>
#include <windows.h>

#pragma comment(lib,"winmm.lib")

int main()
{
	while (1)
	{
		int StartTime;
		StartTime = GetTickCount64();

		while (GetTickCount64() - StartTime >= 1000)
		{
			printf_s("½ÇÇà\n");
		}

	}

	return 0;
}