//CStateIntro.h
#ifndef CSTATEPLAY_H
#define CSTATEPLAY_H

#include <vector>
#include <string>
#include "CGameState.h"
#include "Console.h"
#include "Keystatus.h"
#include "CTimer.h"

class CStatePlay:public CGameState{
public:
  CStatePlay();
  ~CStatePlay();
  void Initialize();
  CGameState* Update(double timeDifference);
  void Render(Console& con);
  void AddTransitionEvent(int event, CGameState* p_Next);

private:
  std::vector<TRANSITION_EVENT> m_TE; //stores all transition events
  int m_event;
  CTimer m_TimerFrameRate;
};

#endif