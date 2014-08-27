#include "GameMainObject.h"
#include "GameMain.h"
#include "header.h"
#include "templates.h"
#include "JPGImage.h"


GameMainObject::GameMainObject(BaseEngine* pEngine )
				: DisplayableObject( pEngine )		
{

	counterTime = 0;

	m_iPlayerSpriteX = 0;
	m_iPlayerSpriteY = 0;

	velocityX = 0;
	velocityY = 0;

	onGround = true;
	jumpAgain = true;

	
	image.LoadImage("spritetrial.jpg");
	
	m_iDrawHeight=image.GetHeight();
	m_iDrawWidth=image.GetWidth();

	m_iStartDrawPosX=-m_iDrawWidth/2;
	m_iStartDrawPosY=-m_iDrawHeight/2;

	m_iPreviousScreenX=m_iCurrentScreenX = m_iCurrentScreenXObject = 400;
	m_iPreviousScreenY=m_iCurrentScreenY = m_iCurrentScreenYObject = 400;

	SetVisible(false);
	
}

GameMainObject::~GameMainObject(void)
{
}



void GameMainObject::Draw(void)
{

	if(!IsVisible())
	{
		return;
	}

	image.RenderImageWithMask(m_pEngine->GetForeground(),m_iPlayerSpriteX,m_iPlayerSpriteY,m_iCurrentScreenX+m_iStartDrawPosX,m_iCurrentScreenY+m_iStartDrawPosY,121,120);

	StoreLastScreenPositionAndUpdateRect();
}

bool GameMainObject::isOnGround()
	{
		if((m_iCurrentScreenY+m_iDrawHeight)==521)
		{
			return true;
		}
		return false;
		

	}




void GameMainObject::DoUpdate(int iCurrentTime)
{

	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	
	counterTime++;

	if(counterTime > 7)
	{
		counterTime = 0;

	if (m_iPlayerSpriteX == 0)
	{
		m_iPlayerSpriteX +=121;

	}
	
	else if(m_iPlayerSpriteX == 121)
	{
		m_iPlayerSpriteX +=121;
	}
	
	else if(m_iPlayerSpriteX == 242)
	{
		m_iPlayerSpriteX +=121;
	}

	else if(m_iPlayerSpriteX == 363)
	{
		m_iPlayerSpriteX +=121;	
	}

	else if(m_iPlayerSpriteX == 484)
	{
		m_iPlayerSpriteX +=121;	
	}
	
	else
	{
		m_iPlayerSpriteX = 0;
	}
	
	}

	if(isOnGround())
	{

		velocityX*=0.9;

		if(GetEngine()->IsKeyPressed(SDLK_SPACE))
		{
			if(jumpAgain == true){
				velocityY=-10;
				jumpAgain = false;
			}

		}
		else
		{
			jumpAgain = true;
		}

	}

	if(!isOnGround())
	{
		velocityY+=0.5;
	}

	m_iCurrentScreenY += velocityY+(0.5);
	m_iCurrentScreenYObject = m_iCurrentScreenY;

	if((m_iCurrentScreenY+m_iDrawHeight)>=521)
	{
		m_iCurrentScreenY=521-m_iDrawHeight;
		m_iCurrentScreenYObject = m_iCurrentScreenY;
	}



	RedrawObjects();
	
}


int GameMainObject::currentPositionX(void)
{
	return m_iCurrentScreenXObject;
}




int GameMainObject::currentPositionY(void)
{
	return m_iCurrentScreenYObject;
}
