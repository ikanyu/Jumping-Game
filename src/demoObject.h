#pragma once
#include "displayableobject.h"


class demoObject :
	public DisplayableObject
{
public:
	demoObject(BaseEngine* pEngine);
	~demoObject(void);
	void Draw(void);
};

