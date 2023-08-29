#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include "color.h"
#include "Position.h"
#include <unistd.h>
using namespace std;
class Menu
    {
        private:
        Position p;
        color Color;
        public:


        Menu()
        {
        SetConsoleTitle( TEXT( "SNAKE WARS" ) ); //changes the title of the console
        }

        int Displaymen()
            {
           
            int choice;
            
             here:
            CONSOLE_FONT_INFOEX cfi;
            cfi.cbSize = sizeof(cfi);
            cfi.nFont = 6;
            cfi.dwFontSize.X = 20;                   // Width of each character in the font
            cfi.dwFontSize.Y = 20;                  // Height
            cfi.FontWeight = FW_NORMAL;
            p.setposition(0,3);
            wcscpy(cfi.FaceName, L"Ariel"); // Choose your font
            SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
            Color.Settextcolor(8);
            cout << setw(50) <<"WELCOME TO SNAKE WARS" << endl;
            Color.Settextcolor(3);
            p.setposition(4,10);
            cout << "Please choose which mode you want to play " << endl;
            cout << endl;
            p.setposition(4,13);
            cout << "1.Snake rush" << endl;
            p.setposition(4,14);
            cout << "2.Two player Snake" << endl;
            p.setposition(4,17);
            Color.Settextcolor(6);
            cout << "Made by Fahim Baig (p20-0065) , Aizaz Ali (P20-0060) , Taha Imran" << endl;
            cin >> choice;

            
            if (choice == 1) 
                {
                    p.setposition(0,0);
                    return 1;
                }
                else if (choice == 2)
                {
                    return 2;
                }
                else    
                {
                    cfi.dwFontSize.X = 30;
                    cfi.dwFontSize.Y = 30;
                    system("CLS");
                    cout << "Invalid choice" << endl;
                    sleep(5);
                    system("CLS");
                    

                    goto here;
                }

            
            }
    };
