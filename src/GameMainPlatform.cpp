#include "GameMainPlatform.h"
#include "GameMain.h"
#include "GameMainObject.h"
#include "header.h"
#include "templates.h"
#include "JPGImage.h"
#include "GameMainFruit.h"



GameMainPlatform::GameMainPlatform(GameMain* pEngine, int iMapX, int iMapY)
: DisplayableObject( pEngine )
, m_pMainEngine( pEngine )
, m_iMapX(iMapX)
, m_iMapY(iMapY)
, m_iDir(0)
{
	standPlatform.LoadImage("platform4.png");
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = -25 + 150;
	m_iStartDrawPosY = -25 + 150;

	// Record the ball size as both height and width
	m_iDrawWidth = 150;
	m_iDrawHeight = 150;
	
	// Out item at specific coordinates
	m_iPreviousScreenX = m_iCurrentScreenX = iMapX*50+25+25;
	m_iPreviousScreenY = m_iCurrentScreenY = iMapY*50+25+40;


	
	// And make it visible
	SetVisible(false);
	int counter=0;
	
}


GameMainPlatform::~GameMainPlatform(void)
{
}




void GameMainPlatform::Draw(void)
{
	if(!IsVisible())
	{
		return;
	}
	//int iSize = 25;

	//printf("reach draw \n");
	//standPlatform.RenderImage(m_pEngine->GetBackground(),0,0,m_iCurrentScreenX+m_iStartDrawPosX,m_iCurrentScreenY+m_iStartDrawPosY,900,110);
	//m_pMainEngine->DrawScreenRectangle();
	StoreLastScreenPositionAndUpdateRect();
}


void GameMainPlatform::DoUpdate(int iCurrentTime)
{

	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	
	counter++;
	if (counter>100){
		counter=0;
	}
	
	//m_iCurrentScreenX -= 10;
	
	
	if(m_iCurrentScreenX == -250)
	{
		m_iCurrentScreenX = 770;
	}


	RedrawObjects();
	
}
