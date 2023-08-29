#include <windows.h>

#ifndef Included_Position_H
#define Included_Position_H
class Position 
    {
        public:
    #define RIGHT 0
    #define UP 1
    #define LEFT 2
    #define DOWN 3
    #define EXIT -1
        void setposition(short int x , short int y)
            {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = {x, y};
        SetConsoleCursorPosition(h, pos);
            }

    void gotoxy(int column, int row)
{
	HANDLE hStdOut;
	COORD coord;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	coord.X = column;
	coord.Y = row;
	SetConsoleCursorPosition(hStdOut, coord);
}

void clearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells and cell attributes in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,		//handle to console screen buffer
		(TCHAR) ' ',	//character to write to the buffer
		cellCount,		//number of cells to write to
		homeCoords,		//coordinates of first cell
		&count			//receives the number of characters written
		)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,			//handle to console screen buffer
		csbi.wAttributes,	//Character attributes to use
		cellCount,			//Number of cells to set attribute
		homeCoords,			//Coordinate of first cell
		&count				//receives the number of characters written
		)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}
int oppositeDirection(int input1, int input2)
{
	if (input1 == LEFT && input2 == RIGHT)
		return 1;
	if (input1 == RIGHT && input2 == LEFT)
		return 1;
	if (input1 == UP && input2 == DOWN)
		return 1;
	if (input1 == DOWN && input2 == UP)
		return 1;

	return 0;
}

    };

#endif