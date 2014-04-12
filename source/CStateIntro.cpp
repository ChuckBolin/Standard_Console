#include "..\include\CStateIntro.h"

CStateIntro::CStateIntro(){
  m_TimerFrameRate.Initialize();
}

CStateIntro::~CStateIntro(){

}

void CStateIntro::Initialize(){
  
}

CGameState* CStateIntro::Update(double timeDifference){
  m_event = GO_NO_WHERE;

  //process this code for the very first Update(...) call
  static bool bFirstTime = false;
  if(bFirstTime == false){
    //HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    //COORD cursorPosition = {5,5};
    //::SetConsoleCursorPosition(hIn, cursorPosition);//gives intro screen focus
    //::SetFocus((HWND)hIn);    
    bFirstTime = true;
  }

  //check user interface
  INPUT_RECORD InRec = GetConsoleInputInfo();

  /*GetNumberOfConsoleInputEvents(hIn, &EventCount);
        while (EventCount > 0)
        {
            ReadConsoleInput(hIn,
                             &InRec,
                             1,
                             &NumRead);
*/

  
  //key press events
  if(InRec.EventType == KEY_EVENT){
    if(InRec.Event.KeyEvent.uChar.AsciiChar == VK_RETURN)
      m_event = GO_MENU;

  }
  //mouse events
  else if(InRec.EventType == MOUSE_EVENT){
    
    if(InRec.Event.MouseEvent.dwButtonState == 0x01){
      //con.write(1,1,InRec.Event.MouseEvent.dwMousePosition.X);
      //con.write(4,1,InRec.Event.MouseEvent.dwMousePosition.Y);
      //m_mouseX = InRec.Event.MouseEvent.dwMousePosition.X;
      //m_mouseY = InRec.Event.MouseEvent.dwMousePosition.Y;
    }
    else if(InRec.Event.MouseEvent.dwButtonState == 0x02){
      m_event = GO_MENU;
    }
    else if(InRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED){
      m_mouseX = InRec.Event.MouseEvent.dwMousePosition.X;
      m_mouseY = InRec.Event.MouseEvent.dwMousePosition.Y;
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

void CStateIntro::Render(Console& con){

  static int frameCount = 0;

  con.setBackgroundColor(1);
  con.cls();
  
  //con.clrscr();
  //con.setBackgroundColor(1);
  
  con.setColor(15);
  con.write(10,0,"Introduction Screen - Press ENTER to continue!");
  con.write(10,1,"or Right Click the mouse");

  for(int i = 0; i < 50; ++i){
    con.setColor(2 + i);
    con.write(i,i,i);
  }

  //display framerate to console title
  frameCount++;
  char buffer[256];
  if(m_TimerFrameRate.GetTimer(1.0)){
    ::sprintf(buffer,"%d FPS", frameCount);
    con.setTitle(buffer);
    frameCount=0;
  }

  COORD maxSize = con.GetMaximumScreenSize();
  con.write(15,13,"Max Size: ");
  con.write(25,13, maxSize.X);
  con.write(30,13, maxSize.Y); 
  con.write(15,14,"Mouse: ");
  con.write(25,14,m_mouseX);
  con.write(30,14,m_mouseY);
  con.write(15,15,"Actual Size: ");
  COORD size = con.GetScreenSize();
  con.write(30,15,size.X);
  con.write(35,15,size.Y);
  con.write(15, 16, "Screen Size: ");
  con.write(30,16, con.GetScreenWidth());
  con.write(40,16, con.GetScreenHeight());
  con.write(15,17,"Font Size: ");
  con.write(30,17, con.GetFontWidth());
  con.write(40,17, con.GetFontHeight());

  for(int i = 0; i <3; ++i){
    con.setColor(14);
    con.writeAscii(m_mouseX + i, m_mouseY, 219); 
    con.writeAscii(m_mouseX + i, m_mouseY + 1, 219);

    con.setColor(12);
    con.writeAscii(m_mouseX + i - 3, m_mouseY + 2, 219); 
    con.writeAscii(m_mouseX + i - 3, m_mouseY + 3, 219);

    con.setColor(10);
    con.writeAscii(m_mouseX + i, m_mouseY + 2, 219); 
    con.writeAscii(m_mouseX + i, m_mouseY + 3, 219);

    con.setColor(11);
    con.writeAscii(m_mouseX + i + 3, m_mouseY + 2, 219); 
    con.writeAscii(m_mouseX + i + 3, m_mouseY + 3, 219);
  }

  con.flip();
}

void CStateIntro::AddTransitionEvent(int event, CGameState* p_Next){
  TRANSITION_EVENT te;
  te.event=event;
  te.p_gso = p_Next;

  m_TE.push_back(te);
}