#pragma once
#include "InversionRendering.h"

class State;

class Player : public Object
{
public:
	bool			Init	()override;
	bool			Frame	()override;
//	bool			Render	()override;
	bool			Release	()override;
private:

};