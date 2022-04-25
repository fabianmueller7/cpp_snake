#include <iostream>
#include<windows.h>
#include <conio.h>
#include <vector>
using namespace std;

void display() 
{

}

void gameloop(int **field, int snakelength, int fieldheight, int fieldwidth) 
{
    while(true) {
        cout << "Number: ";
        cout << field[10][10];
    }
}

int** setupfield(int height, int width) 
{
    int** field = 0;

    for (int h = 0; h < height; h++)
    {
        field[h] = new int[width];

        for (int w = 0; w < width; w++)
        {
            field[h][w] = 0;
        }
    }

    //add a fruit
    field[20][20] = -1; 

    return field;
} 

void startgame() 
{
    int snakelength = 4;
    int fieldheight = 100;
    int fieldwidth = 100;
    gameloop(setupfield(fieldheight,fieldwidth), snakelength, fieldheight, fieldwidth);

}

int main() 
{
    startgame();
    return 0;
}