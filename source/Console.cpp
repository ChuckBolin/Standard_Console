//Console.cpp
#include "..\include\Console.h"

//constructor...initialized object
Console::Console()
{
	mBackColor = 0;			//black
	mForeColor = 7;			//white
	mScreenNumber = 2;	//first page to write to is hScreen1

 //system("mode con: cols=80 lines=50");
 //system("cls");
  //::SetConsoleCP(1250);
  //fullScreen(); //removed from this game
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  hScreen0 = CreateConsoleScreenBuffer(GENERIC_READ |GENERIC_WRITE,0,NULL,CONSOLE_TEXTMODE_BUFFER,NULL);
	hScreen1 = CreateConsoleScreenBuffer(GENERIC_READ |GENERIC_WRITE,0,NULL,CONSOLE_TEXTMODE_BUFFER,NULL);
	hScreen2 = CreateConsoleScreenBuffer(GENERIC_READ |GENERIC_WRITE,0,NULL,CONSOLE_TEXTMODE_BUFFER,NULL);
  //::SetConsoleMode(hScreen0, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);
  //::SetConsoleMode(hScreen1, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);
  //::SetConsoleMode(hScreen2, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);


 //COORD c;
 //c.x = 80;
 //c.y = 50;
 //::SetConsoleDisplayMode(hScreen0, CONSOLE_WINDOWED_MODE, c);
 //HWND console = GetConsoleWindow();
 //RECT r;
 //GetWindowRect(console, &r); //stores the console's current dimensions
 //r.left = 400;
  //MoveWindow(window_handle, x, y, width, height, redraw_window);
// MoveWindow(console, r.left, r.top, 800, 600, TRUE);

// HWND hwnd = GetConsoleWindow();
	//int newX		= 0; // We will ignore this parameter by using the SWP_NOMOVE flag in SetWindowPos
	//int newY		= 0; // We will ignore this parameter by using the SWP_NOMOVE flag in SetWindowPos
	//int newWidth	= 600;	// New Width in Pixels
	//int newHeight	= 600;	// New Height in Pixels
	// Position the console window so that the left and right corners are not changed but the height and width are.
//	SetWindowPos(console, HWND_TOP, newX, newY, newWidth, newHeight, SWP_NOMOVE); // Using SWP_NOMOVE will cause newX and new 
 ShowWindow( GetConsoleWindow(), SW_SHOWMAXIMIZED );//SW_MAXIMIZE);
 SetConsoleSize(80,50);

// ::SetConsoleActiveScreenBuffer(hScreen0);


 //system("mode con: cols=80 lines=50");
  //HMENU hMenu = GetSystemMenu ( (HWND)hScreen0, TRUE);
 //::SetConsoleWindowInfo
	//::DeleteMenu( hMenu, 0, MF_BYPOSITION); // disable 'Maximize'

 

 
 CONSOLE_CURSOR_INFO cci;
 cci.bVisible = false;
 cci.dwSize= 100;

 ::SetConsoleCursorInfo(hScreen1, &cci);
 ::SetConsoleCursorInfo(hScreen2, &cci);
 ::SetConsoleCursorInfo(hScreen0, &cci);

 CONSOLE_SCREEN_BUFFER_INFO cbsi = GetScreenBufferInfo();
 m_screenSize = cbsi.dwSize;
 m_cursorPosition = cbsi.dwCursorPosition;
 m_maximumSize.X = cbsi.dwMaximumWindowSize.X;
 m_maximumSize.Y = cbsi.dwMaximumWindowSize.Y;
}

void Console::fullScreen(void){
  typedef BOOL (WINAPI *PROCSETCONSOLEDISPLAYMODE)(HANDLE,DWORD,LPDWORD);
  typedef BOOL (WINAPI *PROCGETCONSOLEDISPLAYMODE)(LPDWORD);
  PROCSETCONSOLEDISPLAYMODE SetConsoleDisplayMode;
  PROCGETCONSOLEDISPLAYMODE GetConsoleDisplayMode;

  HMODULE hKernel32 = GetModuleHandleA("kernel32");//add A
  SetConsoleDisplayMode = (PROCSETCONSOLEDISPLAYMODE)GetProcAddress(hKernel32,"SetConsoleDisplayMode");
  GetConsoleDisplayMode = (PROCGETCONSOLEDISPLAYMODE)GetProcAddress(hKernel32,"GetConsoleDisplayMode");
  
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD dwOldMode;
  SetConsoleDisplayMode(hOut,1,&dwOldMode);
}

void Console::setTitle(std::string title){
  ::SetConsoleTitle(title.c_str());
}

//sets color of background screen...applies to hScreen1 and hScreen2
void Console::setBackgroundColor(int backColor)
{
  if(backColor < 0 || backColor > 15)
		backColor = 0; //default is black

	mBackColor = backColor;
  
}

//sets forecolor of text
void Console::setColor(int foreColor)
{
  if(foreColor < 0 || foreColor > 15)
		foreColor = 7; //default is white

	mForeColor = foreColor;
}

void Console::write(int x, int y, float value){
  std::ostringstream oss;
  std::string svalue;

  oss << value;
  svalue = oss.str();
  write(x, y, svalue);
}

void Console::write(int x, int y, int value){
  std::ostringstream oss;
  std::string svalue;

  oss << value;
  svalue = oss.str();
  write(x, y, svalue);
}

void Console::write(int x, int y, double value){
  std::ostringstream oss;
  std::string svalue;

  oss << value;
  svalue = oss.str();
  write(x, y, svalue);
}

void Console::write(int x, int y, std::string sText)
{
  if(x < 0 || x >  m_maximumSize.X - 1)
		x = 0;
	if(y < 0 || y > m_maximumSize.Y - 1)
		y = 0;

	mPos.X = x;
	mPos.Y = y;
   
  CONSOLE_CURSOR_INFO cci;
  cci.bVisible = false;
  cci.dwSize= 1;

  mwColors = mBackColor * 16 + mForeColor;
  
	if(mScreenNumber == 1){
	  ::SetConsoleCursorPosition(hScreen1,mPos);
    for(int i = 0; i < (int)sText.length();i++){
      ::WriteConsoleOutputAttribute(hScreen1, &mwColors,1,mPos,&mWritten);
      mPos.X++;
    }
    mPos.X -= (int)sText.length();
    ::WriteConsoleOutputCharacter(hScreen1,sText.c_str(),sText.length(),mPos,&mWritten);
	}
	else if(mScreenNumber == 2){
    ::SetConsoleCursorPosition(hScreen2,mPos);
    for(int i = 0; i < (int)sText.length();i++){
      ::WriteConsoleOutputAttribute(hScreen2, &mwColors,1,mPos,&mWritten);
      mPos.X++;
    }
    mPos.X -= (int)sText.length();
    ::WriteConsoleOutputCharacter(hScreen2,sText.c_str(),sText.length(),mPos,&mWritten);
	}
}

//pass an ascii value to this function for special
//characters such as extended ASCII values
void Console::writeAscii(int x, int y, int ascii)
{
  std::ostringstream oss;
  std::string sText;

  if(x < 0 || x >  m_maximumSize.X - 1)
		x = 0;
	if(y < 0 || y > m_maximumSize.Y - 1)
		y = 0;
  
	mPos.X = x;
	mPos.Y = y;
  
  CONSOLE_CURSOR_INFO cci;
  cci.bVisible = false;
  cci.dwSize= 1;

  mwColors = mBackColor * 16 + mForeColor;
  
  if(ascii >= 0 && ascii <= 255){
    oss << (char)ascii;
    sText = oss.str();

	  if(mScreenNumber == 1){
	    ::SetConsoleCursorPosition(hScreen1,mPos);
      for(int i = 0; i < (int)sText.length();i++){
        ::WriteConsoleOutputAttribute(hScreen1, &mwColors,1,mPos,&mWritten);
        mPos.X++;
      }
      mPos.X -= (int)sText.length();
      ::WriteConsoleOutputCharacter(hScreen1,sText.c_str(),sText.length(),mPos,&mWritten);
      ::SetConsoleCursorInfo(hScreen1, &cci);
	  }
	  else if(mScreenNumber == 2){
      ::SetConsoleCursorPosition(hScreen2,mPos);
      for(int i = 0; i < (int)sText.length();i++){
        ::WriteConsoleOutputAttribute(hScreen2, &mwColors,1,mPos,&mWritten);
        mPos.X++;
      }
      mPos.X -= (int)sText.length();
      ::WriteConsoleOutputCharacter(hScreen2,sText.c_str(),sText.length(),mPos,&mWritten);
      ::SetConsoleCursorInfo(hScreen2, &cci);
	  }
  }
}
  
void Console::writeAsciiLine(int x, int y, int ascii, int num){
  setColor(0);
  for(int i = 0; i < num; i++)
    writeAscii(x + i, y, ascii);
}


//positions the cursor on the screen (0..79, 0..24)
void Console::posCursor(int x, int y)
{
  if(x < 0 || x >  m_maximumSize.X - 1)
		x = 1;
	if(y < 0 || y > m_maximumSize.Y - 1)
		y = 1;
	
	mPos.X = x;
	mPos.Y = y;
	
	if(mScreenNumber == 1){
    ::SetConsoleTextAttribute(hScreen1, mBackColor * 16 + mForeColor);
    ::SetConsoleCursorPosition(hScreen1,mPos);
	}
	else if(mScreenNumber == 2){
    ::SetConsoleTextAttribute(hScreen2, mBackColor * 16 + mForeColor);
    ::SetConsoleCursorPosition(hScreen2,mPos);
	}
}

//swaps hScreen1 and hScreen2
void Console::flip()
{
      //::SetConsoleActiveScreenBuffer(hScreen1);
//mScreenNumber = 2;
      //return;
	if(mScreenNumber == 1){
    ::SetConsoleActiveScreenBuffer(hScreen1);
    mScreenNumber = 2;
	}
	else if(mScreenNumber == 2){
    ::SetConsoleActiveScreenBuffer(hScreen2);
    mScreenNumber = 1;
	}
   ShowWindow( GetConsoleWindow(), SW_SHOWMAXIMIZED );
}

//clears the screen
void Console::cls()
{
  //system("cls");
  //return;
//mScreenNumber = 2;
  mPos.X = 0;
  mPos.Y = 0;
  DWORD cWritten; 
  WORD wColor = BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; 

  if(mScreenNumber == 1){ 
    FillConsoleOutputCharacter(hScreen1,' ',80*50,mPos,&cWritten);
    FillConsoleOutputAttribute(hScreen1,mwColors,80*50,mPos,&cWritten);
  }
  if(mScreenNumber == 2){ 
    FillConsoleOutputCharacter(hScreen2,' ',80*50,mPos,&cWritten);
    FillConsoleOutputAttribute(hScreen2,mwColors,80*50,mPos,&cWritten);
  }
}

void Console::clrscr(){
  COORD coordScreen = { 0, 0 };
  DWORD cCharsWritten;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD dwConSize;
  //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  if(mScreenNumber == 1){ 
    GetConsoleScreenBufferInfo(hScreen1, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hScreen1, TEXT(' '),
                              dwConSize,
                              coordScreen,
                              &cCharsWritten);
    GetConsoleScreenBufferInfo(hScreen1, &csbi);
    FillConsoleOutputAttribute(hScreen1,
                              csbi.wAttributes,
                              dwConSize,
                              coordScreen,
                              &cCharsWritten);
    SetConsoleCursorPosition(hScreen1, coordScreen);
  }
  if(mScreenNumber == 2){ 
    GetConsoleScreenBufferInfo(hScreen2, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hScreen2, TEXT(' '),
                              dwConSize,
                              coordScreen,
                              &cCharsWritten);
    GetConsoleScreenBufferInfo(hScreen2, &csbi);
    FillConsoleOutputAttribute(hScreen2,
                              csbi.wAttributes,
                              dwConSize,
                              coordScreen,
                              &cCharsWritten);
    SetConsoleCursorPosition(hScreen2, coordScreen);
  }
}

void Console::SetConsoleSize(int width, int height){
  ::SMALL_RECT sr;
  sr.Left = 0;
  sr.Top = 0;
  sr.Right = width - 1;
  sr.Bottom = height - 1;
  COORD size;
  size.X = width;
  size.Y = height;
  ::SetConsoleWindowInfo(hScreen0, true, &sr);//physical window size
  ::SetConsoleWindowInfo(hScreen1, true, &sr);
  ::SetConsoleWindowInfo(hScreen2, true, &sr);
  ::SetConsoleScreenBufferSize(hScreen0, size);//buffer (no scroll bar)
  ::SetConsoleScreenBufferSize(hScreen1, size);
  ::SetConsoleScreenBufferSize(hScreen2, size);
  m_maximumSize.X = width;
  m_maximumSize.Y = height;

}

COORD Console::GetMaximumScreenSize(){
  return ::GetLargestConsoleWindowSize(hStdout);
}

CONSOLE_SCREEN_BUFFER_INFO Console::GetScreenBufferInfo(){
   CONSOLE_SCREEN_BUFFER_INFO csbi; 
   DWORD dwConSize;

   GetConsoleScreenBufferInfo( hScreen1, &csbi );       
   return csbi;
}

int Console::GetScreenWidth(){
  return GetSystemMetrics(SM_CXSCREEN);
}

int Console::GetScreenHeight(){
  return GetSystemMetrics(SM_CYSCREEN);
}

int Console::GetFontWidth(){
  return GetScreenWidth()/ GetMaximumScreenSize().X;
}

int Console::GetFontHeight(){
  return GetScreenHeight()/GetMaximumScreenSize().Y;
}
