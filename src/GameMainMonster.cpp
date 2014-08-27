#include "GameMainMonster.h"
#include "GameMainPlatform.h"
#include "GameMain.h"
#include "GameMainObject.h"
#include "header.h"
#include "templates.h"
#include "JPGImage.h"
#include "GameMainFruit.h"



GameMainMonster::GameMainMonster(GameMain* pEngine, int iMapX, int iMapY,GameMainFruit* pMonsterFruit)
	: DisplayableObject( pEngine )
	, m_pMainEngine( pEngine )
	, m_iMapX(iMapX)
	, m_iMapY(iMapY)
	, m_iDir(0)
{
	lock = false;
	m_MonsterFruit = pMonsterFruit;
	monster.LoadImage("monster1.png");

	m_iStartDrawPosX = -25 + 50;
	m_iStartDrawPosY = -25 + -40;

	m_iDrawWidth = 150;
	m_iDrawHeight = 150;

	// Out item at specific coordinates
	m_iPreviousScreenX = m_iCurrentScreenX = iMapX*50+25+25;
	m_iPreviousScreenY = m_iCurrentScreenY = iMapY*50+25+40;


	hasDied = false;
	// And make it visible
	SetVisible(false);
	int counter=0;
	monsterX = 0;
	monsterY =0;

	differenceX = 0;
	differenceY = 0;
	checkRandomSet = false;
}


GameMainMonster::~GameMainMonster(void)
{
}




void GameMainMonster::Draw(void)
{

	if(!IsVisible())
	{
		return;
	}

	if (!lock){
		m_pObject = (GameMainObject*)m_pMainEngine->GetDisplayableObject(0);
		lock = true;
	}


	monster.RenderImageWithMask(m_pMainEngine->GetForeground(),0,0,m_iCurrentScreenX+m_iStartDrawPosX,m_iCurrentScreenY+m_iStartDrawPosY,54,102);

	StoreLastScreenPositionAndUpdateRect();
}


void GameMainMonster::DoUpdate(int iCurrentTime)
{
	if(checkRandomSet == false)
	{
	randomNumberPosition = 800 + (rand() % ( 1000 - 800 + 1 ) );
	
	checkRandomSet = true;
	}

	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	m_iCurrentScreenXMonster = m_iCurrentScreenX;
	m_iCurrentScreenYMonster = m_iCurrentScreenY;

	m_iCurrentScreenX -= 10;

	if(m_iCurrentScreenX <= -250)
	{
		
		m_iCurrentScreenX = randomNumberPosition;
		SetVisible(true);
		hasDied = false;
		checkRandomSet = false;
	
	}

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

bool GameMainMonster::touchFruit(void)
{


	monsterX = m_pObject->currentPositionX();
	monsterY = m_pObject->currentPositionY();
	

	differenceX = monsterX - currentPositionX();
	differenceY = monsterY - currentPositionY();



	if(differenceY>=-15 && differenceY<=-8 && differenceX<=370 && differenceX>=300)
	{
		SetVisible(false);
		hasDied = true;

		if(!IsVisible())
		{
			if(hasDied = true)
			{
				m_MonsterFruit->deductScore();
			}

		}
	}


	return false;
}


int GameMainMonster::currentPositionX(void)
{
	return m_iCurrentScreenXMonster;
}





int GameMainMonster::currentPositionY(void)
{
	return m_iCurrentScreenYMonster;
}


int GameMainMonster::getgameScore(void)
{
	int MonsterScoreTotal = m_MonsterFruit->getgameScore();
	return MonsterScoreTotal;
}
