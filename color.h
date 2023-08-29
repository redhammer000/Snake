
#include <windows.h>

#ifndef Included_color_H
#define Included_color_H
class color
{

public:
void Settextcolor(int color){
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color );
}



};

#endif