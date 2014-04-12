//CStateIntro.h
#ifndef CSTATEMENU_H
#define CSTATEMENU_H

#include <vector>
#include <string>
#include "CGameState.h"
#include "Console.h"
#include "Keystatus.h"

class CStateMenu:public CGameState{
public:
  CStateMenu();
  ~CStateMenu();
  void Initialize();
  CGameState* Update(double timeDifference);
  void Render(Console& con);
  void AddTransitionEvent(int event, CGameState* p_Next);

private:
  std::vector<TRANSITION_EVENT> m_TE; //stores all transition events
  int m_event;
};

#endif