#include "GameMain.h"
#include "header.h"
#include "templates.h"
#include "GameMainObject.h"
//#include "GameMainPlatform.h"
#include "GameMainFruit.h"
#include "GameMainMonster.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;



GameMain::GameMain()
		: BaseEngine( 10 )
		, m_state(stateInit)
{
	
	resumeTime=0;
	stopTime=0;
	menuBackground.LoadImage("menu2.png");
	checkTime = -1;
	checkSetTimer = false;
	gameScoreTotal = 0;
	
}


GameMain::~GameMain(void)
{
}


void GameMain::SetupBackgroundBuffer(void)
{
	
	switch( m_state )
	{
	case stateInit:
	
	menuBackground.RenderImage(GetBackground(),0,75,0,0,960,600);
	//start game
	DrawBackgroundRectangle(650,100,850,175,0xFFCC99);
	//high score
	DrawBackgroundRectangle(650,200,850,275,0xFFCC99);
	//instruction
	DrawBackgroundRectangle(650,300,850,375,0xFFCC99);
	//quit game
	DrawBackgroundRectangle(650,400,850,475,0xFFCC99);
	break;
	
	case stateMain:
	imageBackground.LoadImage("background1.jpg");
	imageBackground.RenderImage(GetBackground(),0,0,0,0,900,676);
	imageObject->SetVisible(true);
	//imagePlatform->SetVisible(true);
	imageFruit->SetVisible(true);
	imageMonster->SetVisible(true);
	break;

	case stateGameOver:
	highscoreBackground.LoadImage("highscorebackground.png");
	highscoreBackground.RenderImage(GetBackground(),0,0,0,0,900,600);

	imageObject->SetVisible(false);
	//imagePlatform->SetVisible(false);
	imageFruit->SetVisible(false);
	imageMonster->SetVisible(false);
	DrawBackgroundRectangle(650,500,850,575,0xFFCC99);
	break;

	case stateInstruction:
		
		
		instructionBackground.LoadImage("instructions.png");
		instructionBackground.RenderImage(GetBackground(),0,0,0,0,900,600);
		imageObject->SetVisible(false);
		//imagePlatform->SetVisible(false);
		imageFruit->SetVisible(false);
		imageMonster->SetVisible(false);
		DrawBackgroundRectangle(650,500,850,575,0xFFCC99);
		break;
	}
	
}


int GameMain::InitialiseObjects(void)
{

	
	DrawableObjectsChanged();
	
	DestroyOldObjects();
	

	m_ppDisplayableObjects = new DisplayableObject*[5];
	imageObject =  new GameMainObject(this);
	//imagePlatform = new GameMainPlatform(this,4,5);
	imageFruit = new GameMainFruit(this,5,7,imageObject);
	imageMonster = new GameMainMonster(this,5,7,imageFruit);
	//standPlatformObject = new GameMainPlatform(this,1,2);
	m_ppDisplayableObjects[0] =	imageObject;
	//m_ppDisplayableObjects[1] = imagePlatform;
	m_ppDisplayableObjects[1] = imageFruit;
	m_ppDisplayableObjects[2] = imageMonster;
	m_ppDisplayableObjects[3] = NULL;
	
	return 0;

}


void GameMain::DrawStrings(void)
{
	char fruitScore[30];
	char highscore1[30];
	char highscore2[30];
	char highscore3[30];
	char highscore4[30];
	char highscore5[30];
	
	sprintf(fruitScore,"Score: %d",imageFruit->getgameScore());
	sprintf(highscore1,"%d", hscore[0]);
	sprintf(highscore2,"%d", hscore[1]);
	sprintf(highscore3,"%d", hscore[2]);
	sprintf(highscore4,"%d", hscore[3]);
	sprintf(highscore5,"%d", hscore[4]);

	switch( m_state )
	{
	case stateInit:
		CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
		
		DrawScreenString( 670,125, "Start Game", 0xCC6666 , NULL);
		DrawScreenString(670, 225, "High Score" ,0xCC6666,NULL);
		DrawScreenString(670, 325, "Instructions" ,0xCC6666,NULL);
		DrawScreenString(670, 425, "Quit" ,0xCC6666,NULL);
		SetNextUpdateRect( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
		break;
	case stateMain:
		CopyBackgroundPixels( 0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/ );
		DrawScreenString( 250, 10, "Fruit Game", 0xffffff, NULL );
		DrawScreenString( 550, 10, fruitScore , 0xffffff, NULL );
		SetNextUpdateRect( 0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/ );
		break;
	case statePaused:
		CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
		DrawScreenString( 200, 300, "Paused. Press KEY 'P' to continue", 0xffffff, NULL );
		SetNextUpdateRect( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
		break;
	case stateGameOver:
		DrawScreenString(400,200,highscore1, 0x000000,NULL);
		DrawScreenString(400,250,highscore2, 0x000000,NULL);
		DrawScreenString(400,300,highscore3, 0x000000,NULL);
		DrawScreenString(400,350,highscore4, 0x000000,NULL);
		DrawScreenString(400,400,highscore5, 0x000000,NULL);
		DrawScreenString(720, 520, "Back" ,0xCC6666,NULL);
		break;
	case stateInstruction:
		DrawScreenString(720, 520, "Back" ,0xCC6666,NULL);
		break;
	}
}



void GameMain::KeyDown(int iKeyCode)
{
	// NEW SWITCH
	switch ( iKeyCode )
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		SetExitWithCode( 0 );
		break;
	case SDLK_p: // SPACE Pauses
		switch( m_state )
		{
		case stateInit:
			// Go to state main
			m_state = stateMain;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;
		case stateMain:
			// Go to state paused
			m_state = statePaused;
			stopTime=GetTime();
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;
		case statePaused:
			// Go to state main
			m_state = stateMain;
			resumeTime=GetTime();
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;
		} // End switch on current state
		break; // End of case SPACE
	
	}

}


void GameMain::GameAction(void)
{
	// If too early to act then do nothing
	if ( !TimeToAct() )
		return;

	// Don't act for another 10 ticks
	SetTimeToAct( 13 );

	// NEW SWITCH
	switch( m_state )
	{
	case stateInit:
		break;
	case statePaused:
		break;
	case stateMain:
		// Only tell objects to move when not paused etc
		UpdateAllObjects( GetTime() );
		if(checkSetTimer == false)
		{
			setTimer();
		}
		if(checkTime <= GetTime())
		{
			m_state = stateGameOver;
			SetupBackgroundBuffer();
			checkSetTimer = false;
			loadHighScore();
			compareHscore();
			setHighscore();
			Redraw(true);
			
		}
		break;
	}
}

void GameMain::DrawChanges()
{
	// NEW IF
	if ( m_state == stateInit )
	{
		return; // Do not draw objects if initialising
	
	}
	// Remove objects from their old positions
	UndrawChangingObjects();
	// Draw the text for the user
	DrawStrings();
	// Draw objects at their new positions
	DrawChangingObjects();
}

void GameMain::MouseDown( int iButton, int iX, int iY )
{
	switch( m_state )
	{
		case stateInit:
		if ( iButton == SDL_BUTTON_LEFT ) 
		{

			if(iX>=650 & iX<=850 & iY>=100 & iY<=175)
			{
				m_state = stateMain;
				startAgain();
				SetupBackgroundBuffer();
				Redraw(true);
			}

			else if(iX>=650 & iX<=850 & iY>=200 & iY<=275)
			{
				m_state = stateGameOver;
				SetupBackgroundBuffer();
				loadHighScore();
				Redraw(true);
			}

			else if(iX>=650 & iX<=850 & iY>=300 & iY<=375)
			{
				m_state = stateInstruction;
				SetupBackgroundBuffer();
				Redraw(true);
			}

			else if(iX>=650 & iX<=850 & iY>=400 & iY<=475)
			{
				SetExitWithCode( 0 );
			}

		}
		break;

		case stateInstruction:
			if ( iButton == SDL_BUTTON_LEFT ) 
			{
			if(iX>=650 & iX<=850 & iY>=500 & iY<=575)
			{
				m_state = stateInit;
				SetupBackgroundBuffer();
				Redraw(true);
			}

			}
		break;

		case stateGameOver:
			if ( iButton == SDL_BUTTON_LEFT ) 
			{
			if(iX>=650 & iX<=850 & iY>=500 & iY<=575)
			{
				m_state = stateInit;
				SetupBackgroundBuffer();
				Redraw(true);
			}
			}
			break;
	}

	


}


void GameMain::setTimer(void)
{
	checkTime = GetTime() + 15000;
	checkSetTimer = true;
}


void GameMain::loadHighScore(void)
{
	string line;
	int i = 0;
	ifstream loadhighscoreFile ("highscore.txt");
	while ( getline (loadhighscoreFile,line)) {
		hscore[i] =  atoi(line.c_str());
		//printf("%d\n",hscore[i]);
		i++;
	}
	loadhighscoreFile.close();
}

void GameMain::setHighscore() {
	ofstream sethighscoreFile("highscore.txt");
	if (sethighscoreFile.is_open())
	{
		for (int i = 0; i < 5; i++){
			sethighscoreFile << hscore[i] << "\n";
		}
		sethighscoreFile.close();
		gameScoreTotal = 0;
	}
}

void GameMain::compareHscore() {
	gameScoreTotal = imageFruit->getgameScore();
	if(gameScoreTotal<=0)
	{
	gameScoreTotal = 0;
	}

	for (int i =0;i<5;i++){
		if (gameScoreTotal>=hscore[i]) {
			for (int j = 4;j>i;j-- ){
			hscore[j]=hscore[j-1];
			}
			hscore[i] = gameScoreTotal;
			break;
			}
		if(gameScoreTotal<=hscore[i])
		{
			for(int j = 4; j<i;j++)
			{
			hscore[j]=hscore[j+1];
			}
			hscore[i] = gameScoreTotal;
			break;
		}


		std::cout<<hscore[i]<<std::endl;
	}
}


void GameMain::startAgain(void)
{
	m_state = stateMain;
	resumeTime=0;
	stopTime=0;
	menuBackground.LoadImage("menu2.png");
	checkTime = -1;
	checkSetTimer = false;
	gameScoreTotal = imageFruit->getgameScore();
	gameScoreTotal = 0;
}
