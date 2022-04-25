#include <iostream>
#include<windows.h>
#include <conio.h>
using namespace std;

void clear() 
{
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

void gotoxy(int x, int y) 
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void control()
{

}

void display(int **field, int height, int width) 
{
        for (int h = 0; h < height; h++)
    {
        cout << endl;

        for (int w = 0; w < width; w++)
        {
            gotoxy(w + 1, h + 1);
            if(field[h][w] > 0)
            {
                cout << "S";
            }
            else if(field[h][w] < 0)
            {
                cout << "F";
            }
            else {
                cout << " ";
            }
        }
    }
}

void updatefield(int **field, int* snakelength, int height, int width, COORD cposition)
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if(field[h][w] > 0)
            {
                field[h][w] -= 1;
            }
        }
    }

    if(field[cposition.Y][cposition.X] == -1){
        *snakelength += 1;
    }

    field[cposition.Y][cposition.X] = *snakelength;
}

void gameloop(int **field, int startinglength, int fieldheight, int fieldwidth, COORD startingposition) 
{
    int length = startinglength;
    COORD cposition = startingposition;
    int heading = 1;

    clear();

    while(true) 
    {
        Sleep(500);
        updatefield(field, &length, fieldheight, fieldwidth, cposition);
        cposition.X -= 1; 
        display(field, fieldheight, fieldwidth);
        _getch();
    }
}

int** setupfield(int height, int width) 
{
    int** field = 0;
    field = new int*[height]; 
    for (int h = 0; h < height; h++)
    {
        field[h] = new int[width];

        for (int w = 0; w < width; w++)
        {
            field[h][w] = 0;
        }
    }

    //add a fruit
    field[5][5] = -1; 

    return field;
} 

void startgame() 
{
    int snakelength = 2;
    int fieldheight = 10;
    int fieldwidth = 10;
    COORD startingposition;
    startingposition.X = 8;
    startingposition.Y = 5;
    gameloop(setupfield(fieldheight,fieldwidth), snakelength, fieldheight, fieldwidth, startingposition);
}

int main() 
{
    startgame();
    return 0;
}