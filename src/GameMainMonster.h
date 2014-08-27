#pragma once
#include "displayableobject.h"
#include "GameMain.h"
#include "BaseEngine.h"
#include "MovementPosition.h"
#include "JPGImage.h"

class GameMain;



class GameMainMonster:
	public DisplayableObject

{
public:
	GameMainMonster(GameMain* pEngine, int iMapX, int iMapY,GameMainFruit* pMonsterFruit);
	~GameMainMonster(void);
	ImageData monster;
	bool touchFruit(void);
	int m_iCurrentScreenXMonster;
	int m_iCurrentScreenYMonster;

	

private:
	/** Pointer to the main engine object */
	GameMain* m_pMainEngine;
	MovementPosition m_oMover;
	GameMainFruit* m_MonsterFruit;
	GameMainObject* m_pObject;

	int m_iMapX;
	int m_iMapY;
	int m_iDir;
	int counter;
	bool hasDied;

	int monsterX;
	int monsterY;

	int differenceX;
	int differenceY;

	bool lock;
	bool checkRandomSet;
	int randomNumberPosition;
public:

	
	void Draw();
	void DoUpdate(int iCurrentTime);
	int currentPositionX(void);
	int currentPositionY(void);
	int getgameScore(void);
};


