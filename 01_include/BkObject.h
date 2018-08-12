#pragma once
#include "Object.h"

class BKObject : public Object
{
public:
	bool			Frame() override;
	bool			Render() override;
};