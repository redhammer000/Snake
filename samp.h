#include <iostream>
#include <time.h>
#include<bits/stdc++.h>
#include <cstdlib>
#include <windows.h>
#include <process.h>
#include <conio.h>
#include "Position.h"
#include "color.h"
using namespace std;
#define MAX 100
#define WIDTH 60
#define HEIGHT 22
#define STARTING_SNAKE_LENGTH 4
#define FOOD 1

//negative values represent areas that cannot be touched or else game over
#define WALL -2
#define SNAKE -1
#define NOTHING 0

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3
#define EXIT -1
#define Bomb -1
int input = RIGHT;
int item = NOTHING;
void userInput(void* id)
{
	do
	{
		int c = _getch();
		switch (c)
		{
		case 'W': case 'w': 
        input = UP; 
        break;
		case 'S': case 's': 
        input = DOWN ; 
        break;
		case 'D': case 'd': 
        input = RIGHT;
         break;
		case 'A': case 'a': 
        input = LEFT ;
         break;
		case 27:
        input = EXIT ;
         break;
		}
	} while (input != EXIT && item >= 0);

	_endthread();
	return;
}
class samp
{

private:
struct Coordinate
{
	int x, y;
};
	int length;
	Coordinate body[WIDTH*HEIGHT];
	int direction;
	int ground[MAX][MAX];
	int foodCounter;
    int checkD{}, bombcount{},seconds{1}, Time{},lastT{},resettime{10};
    
public:

 int dx[5] = { 1, 0, -1, 0 };
 int dy[5] = { 0, -1, 0, 1 };

Position p1;
color c1;

    samp()
    {

    int delay = 100;
	srand(time(NULL));
	
	setGround();
	setSnake();
	updateFood();
	Draw();
	_beginthread(userInput, 0, (void*)0);
	do
	{
        clock_t start_time = clock();
        Time =start_time/CLOCKS_PER_SEC;
        if ( Time != lastT)
        {
            displayClock();

            lastT = Time ;
        }
            
		updateSnake(delay);
		if (item == FOOD)
        {
            Draw();
			updateFood();

        }
	} while (item >= 0 && input != EXIT);

	p1.gotoxy(WIDTH / 2 - 5, HEIGHT / 2 - 2);
	cout << "GAME OVER";
	p1.gotoxy(WIDTH / 2 - 8, HEIGHT / 2 + 2);
	cout << "Your score is " << getFoodCounter() - 1 << "!" << endl;
	p1.gotoxy(WIDTH / 2, HEIGHT / 2);

	_getch();

        }

void setGround()
{
    
	int i, j;
	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
			ground[i][j] = 0;

	for (i = 0; i <= WIDTH + 1; i++)
	{
		//the up/down wall
		ground[0][i] = WALL;
		ground[HEIGHT + 1][i] = WALL;
	}
	for (i = 0; i <= HEIGHT + 1; i++)
	{
		//the diagonal wall
		ground[i][0] = WALL;
		ground[i][WIDTH + 1] = WALL;
	}

    

    
}

void setSnake()
{
	length = STARTING_SNAKE_LENGTH;		//set head of snake to be at the centre
	body[0].x = WIDTH / 2;
	body[0].y = HEIGHT / 2;
	direction = input;
	foodCounter = 0;

	int i;
	for (i = 1; i < length; i++)
	{
		body[i].x = body[i - 1].x - dx[direction];		//if moving right,
		body[i].y = body[i - 1].y - dy[direction];		//body is on the left
	}
	//location of snek
	for (i = 0; i < length; i++)
		ground[body[i].y][body[i].x] = SNAKE;
}

void updateSnake(int delay)
{
	int i;
    c1.Settextcolor(7);
	Coordinate prev[WIDTH*HEIGHT];
	for (i = 0; i < length; i++)
	{
		prev[i].x = body[i].x;
		prev[i].y = body[i].y;
	}

	if (input != EXIT && !p1.oppositeDirection(direction, input))
		direction = input;

	body[0].x = prev[0].x + dx[direction];		//head of snake
	body[0].y = prev[0].y + dy[direction];		//follows the direction

	if (ground[body[0].y][body[0].x] < NOTHING)
	{
		item = -1;
		return;
	}

	if (ground[body[0].y][body[0].x] == FOOD)
	{
		length++;		//increase length
		item = FOOD;
	}
	else
	{
		ground[body[length - 1].y][body[length - 1].x] = NOTHING;
		item = NOTHING;
		p1.gotoxy(body[length - 1].x, body[length - 1].y);
		cout << " ";						
	}

	for (i = 1; i < length; i++)
	{
		body[i].x = prev[i - 1].x;	
		body[i].y = prev[i - 1].y;	
	}

	p1.gotoxy(body[1].x, body[1].y);
	cout << "~";					//replace previous head with body
	p1.gotoxy(body[0].x, body[0].y);
	cout << "X";					//making a new head to the snake so that when it updates there is a head

	//location of snek
	for (i = 0; i < length; i++)
		ground[body[i].y][body[i].x] = SNAKE;

	Sleep(delay);

	return;
}

void updateFood()
{
	int x, y;
	do
	{
		x = rand() % WIDTH + 1;
		y = rand() % HEIGHT + 1;
	} while (ground[y][x] != NOTHING);

	ground[y][x] = FOOD;
	foodCounter++;
	p1.gotoxy(x, y);
	cout << "O"; // making food
}

void makebomb()
{
	int x, y;
	do
	{
		x = rand() % WIDTH + 1;
		y = rand() % HEIGHT + 1;
	} while (ground[y][x] != NOTHING);

	ground[y][x] = Bomb;
	p1.gotoxy(x, y);
    c1.Settextcolor(4);
	cout << "X"; // making bomb
}

void clearbomb()//removing bombs
{
        for (int i = 0 ; i < 100 ; i++ )
            for (int t = 0 ; t < 100 ; t++)
            if(ground[i][t] == Bomb)
            {
        ground[i][t] = NOTHING;
        p1.gotoxy(t, i);
        cout << " ";
            }

}

void Draw()
{   
    if (checkD == 0)
    {
        checkD++;
	p1.clearScreen();
	int i, j;
	for (i = 0; i <= HEIGHT + 1; i++)
	{
		for (j = 0; j <= WIDTH + 1; j++)
		{
			switch (ground[i][j])
			{
			case NOTHING:
				cout << " "; break;
			case WALL:
                c1.Settextcolor(9);
				if ((i == 0 && j == 0)
					|| (i == 0 && j == WIDTH + 1)
					|| (i == HEIGHT + 1 && j == 0)
					|| (i == HEIGHT + 1 && j == WIDTH + 1))
					cout << "#";    //the ends
				else

					if (j == 0 || j == WIDTH + 1)
						cout << "I";    //diagonal wall
					else
						cout << "-";    //up/down walls
				break;
			case SNAKE:
                
				if (i == body[0].y && j == body[0].x)
					cout << "O";
				else
					cout << "+";
				break;
			default:				
				cout << "O";	
			}
		}
		cout << endl;
	}
    p1.gotoxy(WIDTH-60,HEIGHT+3);
    c1.Settextcolor(11);
    printf ("Made by Fahim baig , Aizaz ali , Taha Imran ");
    c1.Settextcolor(7);
    }if (checkD !=0)
    foodCounter++;
        p1.gotoxy((WIDTH-30),HEIGHT+8);
    printf("YOUR SCORE IS : %d" , foodCounter-2);
}

int getFoodCounter()
{
	return foodCounter;
}


void displayClock()
    {
        seconds--;
        resettime--;
        p1.gotoxy((WIDTH-60),HEIGHT+6);
            printf("Time before new bombs appear : %d " , seconds);
        p1.gotoxy((WIDTH-60),HEIGHT+8);
            printf("Time before reset map : %d " , resettime);
        if (seconds == 0)
            {
                seconds = 1;
                makebomb();
            }
        if (resettime == 0)
            {
                resettime = 10;
                clearbomb();
            }
    }
};

