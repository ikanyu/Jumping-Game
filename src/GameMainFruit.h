#pragma once
#include "displayableobject.h"
#include "GameMain.h"
#include "BaseEngine.h"
#include "MovementPosition.h"
#include "JPGImage.h"
#include "GameMainObject.h"

class GameMain;
class GameMainObject;
class GameMainFruit:
	public DisplayableObject
{
public:
	GameMainFruit(GameMain* pEngine, int iMapX, int iMapY,GameMainObject* pFruitObject);
	~GameMainFruit(void);
	ImageData imageFruit;
	int m_iCurrentScreenXFruit;
	int m_iCurrentScreenYFruit;

	
	void Draw();
	void DoUpdate(int iCurrentTime);
	int currentPositionX(void);
	int currentPositionY(void);
	bool touchFruit(void);
	int differenceX;
	int differenceY;
	int gameScore;

	bool hasDied;

	enum FruitType { corn , cucumber};
	//int gamePreviousScore;
	//int gameScoreDifference;

private:
	/** Pointer to the main engine object */
	GameMain* m_pMainEngine;
	MovementPosition m_oMover;
	GameMainObject* m_pObject;

	FruitType m_fruitType;

	int m_iMapX;
	int m_iMapY;
	int m_iDir;
	int counter;
	int objectX;
	int objectY;
	int randomNumberPosition;
	bool checkRandomSet;

	

	
public:
	int getgameScore(void);
	void deductScore(void);
};


