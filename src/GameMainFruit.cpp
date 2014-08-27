#include "GameMainPlatform.h"
#include "GameMain.h"
#include "GameMainObject.h"
#include "header.h"
#include "templates.h"
#include "JPGImage.h"
#include "GameMainFruit.h"



GameMainFruit::GameMainFruit(GameMain* pEngine, int iMapX, int iMapY,GameMainObject* pFruitObject)
: DisplayableObject( pEngine )
, m_pMainEngine( pEngine )
, m_iMapX(iMapX)
, m_iMapY(iMapY)
, m_iDir(0)
{
	

	imageFruit.LoadImage("corn1.png");
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = -25 + 50;
	m_iStartDrawPosY = -25 + 150;
	m_pObject=pFruitObject;

	// Record the ball size as both height and width
	m_iDrawWidth = 150;
	m_iDrawHeight = 150;
	
	// Out item at specific coordinates
	//m_iPreviousScreenX = m_iCurrentScreenX = iMapX*50+25+25;
	//m_iPreviousScreenY = m_iCurrentScreenY = iMapY*50+25+40;
	m_iPreviousScreenX = m_iCurrentScreenX  = m_iCurrentScreenXFruit = 50 ;
	m_iPreviousScreenY = m_iCurrentScreenY = m_iCurrentScreenYFruit = 70;
	//m_pObject = (GameMainFruit*)m_pMainEngine->GetDisplayableObject(0);
	// And make it visible
	
	gameScore = 0;
	hasDied = false;
	randomNumberPosition = 0;
	checkRandomSet = false;

	
	
	SetVisible(false);
	
	
}


GameMainFruit::~GameMainFruit(void)
{
}




void GameMainFruit::Draw(void)
{
	if(!IsVisible())
	{
		return;
	}
	//int iSize = 25;

	//printf("reach draw \n");
	imageFruit.RenderImageWithMask(m_pMainEngine->GetForeground(),0,0,m_iCurrentScreenX+m_iStartDrawPosX,m_iCurrentScreenY+m_iStartDrawPosY,104,134);
	//m_pMainEngine->DrawScreenRectangle();
	StoreLastScreenPositionAndUpdateRect();
}


void GameMainFruit::DoUpdate(int iCurrentTime)
{
	if(checkRandomSet == false)
	{
	randomNumberPosition = 800 + (rand() % ( 1000 - 800 + 1 ) );
	printf("random number %d \n", randomNumberPosition);
	printf("m i current screen x value %d\n",m_iCurrentScreenX);
	checkRandomSet = true;
	}

	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;
	//m_iPreviousScreenX = m_iCurrentScreenX = randomNumberPosition;
	//m_iPreviousScreenY = m_iCurrentScreenY = randomNumberPosition;

	m_iCurrentScreenX -= 10;
	
	m_iCurrentScreenXFruit = m_iCurrentScreenX;

	m_iCurrentScreenY = m_iCurrentScreenYFruit;

	if(m_iCurrentScreenX <= -250)
	{
		
		m_iCurrentScreenX = randomNumberPosition;
		SetVisible(true);
		hasDied = false;
		checkRandomSet = false;
		
	}

	objectX = m_pObject->currentPositionX();
	objectY = m_pObject->currentPositionY();

	touchFruit();
	RedrawObjects();

	if(hasDied == true)
	{
		if(m_iCurrentScreenX >= randomNumberPosition)
	{
		SetVisible(true);
		hasDied = false;
	}
	}

	
}


int GameMainFruit::currentPositionX(void)
{
	return m_iCurrentScreenXFruit;
}




int GameMainFruit::currentPositionY(void)
{
	return m_iCurrentScreenYFruit;
}


bool GameMainFruit::touchFruit(void)
{
	objectX = m_pObject->currentPositionX();
	objectY = m_pObject->currentPositionY();
	
	differenceX = objectX - currentPositionX();
	differenceY = objectY - currentPositionY();

	//printf("differenceY %d \n",differenceY);
	//printf("difference X %d \n",differenceX);

	if(differenceY>=230 && differenceY<=238 && differenceX<=435 && differenceX>=300)
	{
		SetVisible(false);
		hasDied = true;
		
		if(!IsVisible())
		{
			if(hasDied = true)
			{
			gameScore+=1;
			//printf("become disappeared");
			printf("game score now %d " , getgameScore());
		//SetVisible(true);
			}
			
		}
	}

	
	return false;
}


int GameMainFruit::getgameScore(void)
{
	if(gameScore<=0)
	{
		gameScore = 0;
	}


	return gameScore;
}


void GameMainFruit::deductScore(void)
{
	gameScore-=1;
}
