#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"
#include "GameMain.h"
#include "BaseEngine.h"

class GameMainObject :
	public DisplayableObject
{
public:
	GameMainObject(BaseEngine* pEngine );
	~GameMainObject(void);
	void Draw(void);
	ImageData image;
	void DoUpdate(int iCurrentTime);
	bool isOnGround();

	int m_iCurrentScreenXObject;
	int m_iCurrentScreenYObject;

	

private:
	
	int m_iPlayerSpriteX;
	int m_iPlayerSpriteY;
	int counterTime;
	//set object velocity
	float velocityX;
	float velocityY;
	//check object status
	bool jumpAgain;
	bool onGround;

	
public:
	int currentPositionX(void);
	int currentPositionY(void);
};

