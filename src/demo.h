#pragma once
#include "baseengine.h"
class demo :
	public BaseEngine
{
public:
	demo(void);
	~demo(void);
	void SetupBackgroundBuffer(void);
	void MouseDown(int iButton, int iX, int iY);
	void KeyDown(int iKeyCode);
};

