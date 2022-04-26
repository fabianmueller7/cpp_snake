#include <iostream>
#include<windows.h>
#include <conio.h>
#include<thread>
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

void getuserinput(int* direction)
{
    char ch;
    while(true){
        ch = _getch();

        //up 
        if(ch == 'w')
        {
            *direction = 5; //Bits 0101
        }
        //down
        else if(ch == 's')
        {
            *direction = 9; //Bits 1001
        }
        //left
        else if(ch == 'a')
        {
            *direction = 6; //Bits 0110
        }
        //right
        else if(ch == 'd')
        {
            *direction = 10; //Bits 1010
        }
    }
}

void movement(int* direction, COORD* cposition, int width, int height)
{
    //Bits of direction
    //1. bit if Y
    //2. bit if X
    //3. bit if -
    //4. bit if +
    cposition->Y = (cposition->Y + ((*direction >> 2) & 1)*((*direction >> 0) & 1)*(-1) + ((*direction >> 3) & 1)*((*direction >> 0) & 1)*(1) + height)%height;
    cposition->X = (cposition->X + ((*direction >> 2) & 1)*((*direction >> 1) & 1)*(-1) + ((*direction >> 3) & 1)*((*direction >> 1) & 1)*(1) + width)%width;
}

void display(int **field, int height, int width) 
{
    for (int h = 0; h < height; h++)
    {
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
            
            if(h == 0 )
            {
                gotoxy(w+1, h);
                cout << "#";
            }

            if(w == 0 )
            {
                gotoxy(w, h+1);
                cout << "#";
            }

            if(w == width-1 )
            {
                gotoxy(w+2, h+1);
                cout << "#";
            }

            if(h == height-1 )
            {
                gotoxy(w+1, h+2);
                cout << "#";
            }  
        }
    }
}

void generatenewfruit(int **field, int height, int width)
{
    int x;
    int y;

    do{
        y = rand()%height;
        x = rand()%width;
    }while (field[y][x] > 0);

    field[y][x] -= 1; 
}

void updatefield(int **field, int* snakelength, int height, int width, COORD cposition, boolean* lost)
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

    if(field[cposition.Y][cposition.X] == -1)
    {
        *snakelength += 1;
        generatenewfruit(field, height, width);
    }

    if(field[cposition.Y][cposition.X] > 0)
    {
        *lost = true;
    }


    field[cposition.Y][cposition.X] = *snakelength;
}

void gameloop(int **field, int startinglength, int fieldheight, int fieldwidth, COORD startingposition) 
{
    int length = startinglength;
    COORD cposition = startingposition;
    int heading = 6;
    boolean lost = false;
    thread input_thread(getuserinput, &heading);
    input_thread.detach();
    clear();
    
    while(lost == false) 
    {
        updatefield(field, &length, fieldheight, fieldwidth, cposition, &lost);
        display(field, fieldheight, fieldwidth);
        movement(&heading, &cposition, fieldwidth, fieldheight);
        Sleep(500);
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