#include "..\include\CStateQuit.h"

CStateQuit::CStateQuit(){

}

CStateQuit::~CStateQuit(){

}

void CStateQuit::Initialize(){

}

CGameState* CStateQuit::Update(double timeDifference){
  m_event = GO_NO_WHERE;

  //game state transition code...very important
  for(unsigned int i=0; i< m_TE.size(); ++i){
    if (m_TE[i].event == m_event){
      return m_TE[i].p_gso;
    }
  }


  return 0;
}

void CStateQuit::Render(Console& con){
  con.setBackgroundColor(1);
  con.cls();
  con.setColor(15);
  con.write(1,1,"Quit");
  con.flip();

}

void CStateQuit::AddTransitionEvent(int event, CGameState* p_Next){
  TRANSITION_EVENT te;
  te.event=event;
  te.p_gso = p_Next;

  m_TE.push_back(te);
}
