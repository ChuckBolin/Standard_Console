//main.cpp
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include "..\include\CLog.h"
#include "..\include\Keystatus.h"
#include "..\include\Console.h"
#include "..\include\CTimer.h"
//#include "..\include\CINIReader.h"
#include "..\include\CGameState.h"
#include "..\include\CStateIntro.h"
#include "..\include\CStateMenu.h"
#include "..\include\CStatePlay.h"
#include "..\include\CStateQuit.h"
#include "..\include\CStateRules.h"
#include "..\include\CStateScore.h"
#include "..\include\CStateWin.h"
#include "..\include\CStateOver.h"
#include "..\include\CStateIntro.h"
#include "..\include\CConfigData.h"

using namespace std;

//manages game states
CGameState* g_pStateIntro = new CStateIntro;
CGameState* g_pStateMenu = new CStateMenu;
CGameState* g_pStateQuit = new CStateQuit;
CGameState* g_pStateRules = new CStateRules;
CGameState* g_pStateScore = new CStateScore;
CGameState* g_pStatePlay = new CStatePlay;
CGameState* g_pCurrent = 0;
CGameState* g_pNext = 0;

//******************************************************************************
void Initialize(){                      //  I N I T I A L I Z E
//******************************************************************************

  //define transition events for game states
  g_pStateIntro->AddTransitionEvent(GO_MENU, g_pStateMenu);
  g_pStateMenu->AddTransitionEvent(GO_QUIT, g_pStateQuit);
  g_pStateMenu->AddTransitionEvent(GO_RULES, g_pStateRules);
  g_pStateMenu->AddTransitionEvent(GO_SCORE, g_pStateScore);
  g_pStateMenu->AddTransitionEvent(GO_PLAY, g_pStatePlay);
  g_pStateRules->AddTransitionEvent(GO_MENU, g_pStateMenu);
  g_pStateScore->AddTransitionEvent(GO_MENU, g_pStateMenu);
  g_pStatePlay->AddTransitionEvent(GO_MENU, g_pStateMenu);
  
  //perform any required game state initialization
  g_pStateIntro->Initialize();
  g_pStateMenu->Initialize();
  g_pStateQuit->Initialize();
  g_pStateRules->Initialize();
  g_pStateScore->Initialize();
  g_pStatePlay->Initialize();

  //start game
  g_pCurrent = g_pStateIntro;
}

//********************************************************************
// main()
//********************************************************************
int main(){
  //::AllocConsole();

  //instantiate log object and log
  CLog *pLog = CLog::Instance();
  pLog->Log("*********************************************************");
  pLog->Log("Program starting..................");
  pLog->SetDelimiter(':');
  pLog->LogDate();
  pLog->LogTime();
  pLog->Log("************************ *********************************");
  CConfigData cfg;
  cfg.LoadConfigFile("assets//data//config.cfg");

  //initialize setup stuff
  Console con;
  Initialize();
  
  CONSOLE_SCREEN_BUFFER_INFO csbi = con.GetScreenBufferInfo();
  pLog->Log("Screen Buffer Size",csbi.dwSize.X, csbi.dwSize.Y);

  pLog->Log("Window Size",csbi.dwMaximumWindowSize.X, csbi.dwMaximumWindowSize.Y);
  pLog->Log("Left-Top",csbi.srWindow.Left, csbi.srWindow.Top);
  pLog->Log("Right-Bottom",csbi.srWindow.Right, csbi.srWindow.Bottom);
  pLog->Log("Maximum Window Size", csbi.dwMaximumWindowSize.X, csbi.dwMaximumWindowSize.Y);
  //con.SetConsoleSize(80,30);//80,25);
  COORD maxSize = con.GetMaximumScreenSize();
  pLog->Log("Max Size",maxSize.X, maxSize.Y);


  //pLog->Log("g_pCurrent", g_pCurrent);
  //pLog->Log("g_pStateIntro",g_pStateIntro);

  //HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
  //COORD cursorPosition = {5,5};
  //::SetConsoleCursorPosition(hIn, cursorPosition);//gives intro screen focus
  //::SetFocus((HWND)hIn);

  //game timer
  CTimer loopTimer;
  loopTimer.Initialize();
  double timeDelta = 0;

  //main game loop
  //********************************************
  bool quit = false;    
  while(!quit){ 
    timeDelta = loopTimer.GetTimeDifference();
    g_pNext = g_pCurrent->Update(timeDelta);
	  if(NULL != g_pNext)
	  {
      g_pCurrent = g_pNext;
    }
     
    if(g_pCurrent == g_pStateQuit )
      quit = true;

  	// Render our current game object
    g_pCurrent->Render(con);
  }
  //********************************************
  //end game loop

  //free resources
  delete g_pStateIntro;
  delete g_pStateMenu;
  delete g_pStateQuit;
  delete g_pStateRules;
  delete g_pStateScore;
  delete g_pStatePlay;

  //normal termination of game
  pLog->Log("*********************************************************");
  pLog->Log("Program terminating normally..................");
  pLog->SetDelimiter(':');
  pLog->LogTime();
  pLog->Log("*********************************************************");
  
  return 0;
}



 