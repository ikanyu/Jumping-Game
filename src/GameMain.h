#pragma once
#include "baseengine.h"
#include "JPGImage.h"
#include "GameMainObject.h"
#include "GameMainFruit.h"
#include "GameMainMonster.h"

class GameMainObject;
class GameMainPlatform;
class GameMainMonster;

class GameMain :
	public BaseEngine
{
public:
	GameMain(void);
	~GameMain(void);
	void SetupBackgroundBuffer(void);
	int InitialiseObjects(void);
	
	GameMainObject* imageObject;
	GameMainPlatform* imagePlatform;
	GameMainFruit* imageFruit;
	GameMainMonster* imageMonster;

	ImageData imageBackground,menuBackground,highscoreBackground,instructionBackground;
	void DrawStrings(void);
	void KeyDown(int iKeyCode);
	void DrawChanges();
	void GameAction();

	enum State { stateInit, stateMain, statePaused, stateGameOver, stateInstruction };
	
	void MouseDown( int iButton, int iX, int iY );
	

	//GameMainPlatform* standPlatformObject;
private:
	State m_state;
	
	int resumeTime;
	int stopTime;
	int checkTime;
	bool checkSetTimer;
	int gameScoreTotal;
	int hscore[5];
	//GameMainObject* human;
	
public:
	void setTimer(void);
	void loadHighScore(void);
	void setHighscore(void);
	void compareHscore(void);
	void startAgain(void);
};

