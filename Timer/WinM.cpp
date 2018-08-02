#include "Core.h"

class Simple : public Core
{
private:
public:
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE prev, LPWSTR szCmdLine, int cmd)
{
	Simple wd;
	wd.setWindow(hinst);
	wd.Run();

	return 0;
}