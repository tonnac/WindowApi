#include <iostream>
#include <string>
#include <tchar.h>
#include <fstream>
#include <sstream>

using namespace std;
using T_STR = std::basic_string<TCHAR>;


int main()
{
	int a, b, c, d;
	std::string dd;
	ifstream in("SPRITE.txt",ios::out);
	while (!in.eof())
	{
		getline(in, dd);
		istringstream ist(dd);
		ist >> dd >> a;
	}


	return 0;
}