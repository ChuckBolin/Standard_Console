#include "..\include\CStateMenu.h"

CStateMenu::CStateMenu(){

}

CStateMenu::~CStateMenu(){

}

void CStateMenu::Initialize(){

}

CGameState* CStateMenu::Update(double timeDifference){
  m_event = GO_NO_WHERE;

  //check user interface
  INPUT_RECORD InRec = GetConsoleInputInfo();

  //key press events
  if(InRec.EventType == KEY_EVENT){
    if(InRec.Event.KeyEvent.uChar.AsciiChar == VK_ESCAPE)
      m_event = GO_QUIT;

  }
  //mouse events
  else if(InRec.EventType == MOUSE_EVENT){
    
    if(InRec.Event.MouseEvent.dwButtonState == 0x01){
      m_event = GO_QUIT;
      //con.write(1,1,InRec.Event.MouseEvent.dwMousePosition.X);
      //con.write(4,1,InRec.Event.MouseEvent.dwMousePosition.Y);
    }
    else if(InRec.Event.MouseEvent.dwButtonState == 0x02){
    }
    else if(InRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED){
      //g_mouseX = InRec.Event.MouseEvent.dwMousePosition.X;
      //g_mouseY = InRec.Event.MouseEvent.dwMousePosition.Y;
    }
    else{

    }
  }

  //game state transition code...very important
  for(unsigned int i=0; i< m_TE.size(); ++i){
    if (m_TE[i].event == m_event){
      return m_TE[i].p_gso;
    }
  }


  return 0;
}

void CStateMenu::Render(Console& con){
  con.setBackgroundColor(1);
  con.cls();
  con.setColor(15);
  con.write(1,1,"Menu Screen - Press ESC to Quit!");
  con.write(1,2,"or Left Click the mouse");
  con.flip();

}

void CStateMenu::AddTransitionEvent(int event, CGameState* p_Next){
  TRANSITION_EVENT te;
  te.event=event;
  te.p_gso = p_Next;

  m_TE.push_back(te);
}