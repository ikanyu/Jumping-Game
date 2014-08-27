#pragma once
#include "displayableobject.h"
#include "GameMain.h"
#include "BaseEngine.h"
#include "MovementPosition.h"
#include "JPGImage.h"

class GameMain;



class GameMainPlatform:
	public DisplayableObject

{
public:
	GameMainPlatform(GameMain* pEngine, int iMapX, int iMapY);
	~GameMainPlatform(void);
	ImageData standPlatform;

	

private:
	/** Pointer to the main engine object */
	GameMain* m_pMainEngine;
	MovementPosition m_oMover;

	int m_iMapX;
	int m_iMapY;
	int m_iDir;
	int counter;
	
public:

	
	void Draw();
	void DoUpdate(int iCurrentTime);
};


