//Console.h - Character Mode or Console Mode
//Updated January 15, 2008 by Chuck Bolin
//  Improves CLS function and adds additional getters.

#ifndef CONSOLE_H
#define CONSOLE_H
#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>

class Console{
public:
  Console();
  void fullScreen(void);
  CONSOLE_SCREEN_BUFFER_INFO GetScreenBufferInfo();
  void setTitle(std::string title);
  void setBackgroundColor(int backColor);
  void setColor(int foreColor);
	void cls();
  void clrscr();
  void writeAscii(int x, int y, int ascii);
  void writeAsciiLine(int x, int y, int ascii, int num);
	void write(int x, int y, std::string sText);
  void write(int x, int y, float value);
  void write(int x, int y, int value);
  void write(int x, int y, double value);
  COORD GetScreenSize(){return m_screenSize;}
  COORD GetCursorPosition(){return m_cursorPosition;}
  void posCursor(int x, int y);
  void flip();
  void SetConsoleSize(int width, int height);
  COORD GetMaximumScreenSize();
  int GetScreenWidth();
  int GetScreenHeight();
  int GetFontWidth();
  int GetFontHeight();
  
private:
  int mBackColor;
	int mForeColor;
	int mScreenNumber;
	HANDLE hStdout;
	HANDLE hScreen0;
	HANDLE hScreen1;
	HANDLE hScreen2;
  COORD mPos;
  DWORD mWritten; 
  WORD mwColors;//[1];
  COORD m_screenSize;
  COORD m_cursorPosition;
  COORD m_maximumSize;
};

#endif //CONSOLE_H
