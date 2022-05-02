#include "singleplayerthread.h"
#include "singleplayer.h"
#include "ui_singleplayer.h"
#include <iostream>
#include<windows.h>
#include <conio.h>
#include<thread>
#include <QKeyEvent>
#include <QApplication>
using namespace std;

singleplayerthread::singleplayerthread(Ui::Singleplayer *ui, int  *direction, int width)
{
 m_ui = ui;
 m_direction = direction;
 m_width = width;
}

void movement(int* direction, COORD* cposition, int width, int height, int *lastdirection)
{
    //Bits of direction 9=UP, 5=DOWN, 10=LEFT, 6=RIFHT
    //1. bit if Y
    //2. bit if X
    //3. bit if -
    //4. bit if +
    //up
    int nextdirection = *direction;
    if(nextdirection == 5 && *lastdirection != 9)
    {
        nextdirection= 5; //Bits 0101
        *lastdirection = 5;
    }
    //down
    else if(nextdirection == 9 && *lastdirection != 5)
    {
        nextdirection = 9; //Bits 1001
        *lastdirection = 9;
    }
    //left
    else if(nextdirection == 6 && *lastdirection != 10)
    {
        nextdirection = 6; //Bits 0110
        *lastdirection = 6;
    }
    //right
    else if(nextdirection == 10 && *lastdirection != 6)
    {
        nextdirection = 10; //Bits 1010
        *lastdirection = 10;
    }
    else
    {
        nextdirection = *lastdirection;
    }

    cposition->Y = (cposition->Y + ((nextdirection >> 2) & 1)*((nextdirection >> 0) & 1)*(-1) + ((nextdirection >> 3) & 1)*((nextdirection >> 0) & 1)*(1) + height)%height;
    cposition->X = (cposition->X + ((nextdirection >> 2) & 1)*((nextdirection >> 1) & 1)*(-1) + ((nextdirection >> 3) & 1)*((nextdirection >> 1) & 1)*(1) + width)%width;
}


void display(int **field, int height, int width, Ui::Singleplayer *ui, int length)
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if(field[h][w] == length)
            {
                ui->tableWidget->setItem(h, w, new QTableWidgetItem);
                ui->tableWidget->item(h,w)->setBackground(Qt::black);
            }
            else if(field[h][w] > 0)
            {
                ui->tableWidget->setItem(h, w, new QTableWidgetItem);
                ui->tableWidget->item(h,w)->setBackground(Qt::blue);
            }
            else if(field[h][w] < 0)
            {
                ui->tableWidget->setItem(h, w, new QTableWidgetItem);
                ui->tableWidget->item(h, w)->setBackground(Qt::red);
            }
            else {
                ui->tableWidget->setItem(h, w, new QTableWidgetItem);
                ui->tableWidget->item(h, w)->setBackground(Qt::white);
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

void updatefield(int **field, int* snakelength, int height, int width, COORD cposition, boolean* lost, Ui::Singleplayer *ui)
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
        ui->lblScore->setText(QString::number(*snakelength-2));
        generatenewfruit(field, height, width);
    }

    if(field[cposition.Y][cposition.X] > 0)
    {
        *lost = true;
    }


    field[cposition.Y][cposition.X] = *snakelength;
}


void gameloop(int **field, int startinglength, int fieldheight, int fieldwidth, COORD startingposition, Ui::Singleplayer *ui, int* direction, singleplayerthread *thread)
{
    int length = startinglength;
    int lastdirection = 6;
    COORD cposition = startingposition;
    int *heading = direction;
    boolean lost = false;
    *heading = 6;

    while(lost == false)
    {
        movement(heading, &cposition, fieldwidth, fieldheight, &lastdirection);
        updatefield(field, &length, fieldheight, fieldwidth, cposition, &lost, ui);
        display(field, fieldheight, fieldwidth, ui, length);
        Sleep(250);
    }
    ui->btnStart->setDisabled(false);
    ui->cbFieldsize->setDisabled(false);
    thread->exit();
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
    field[(5%width)][(5%width)] = -1;

    return field;
}

void startgame(Ui::Singleplayer *ui, int *direction, singleplayerthread *thread, int width)
{
    int snakelength = 2;
    int fieldheight = width;
    int fieldwidth = width;

    COORD startingposition;
    startingposition.X = 8;
    startingposition.Y = 5;
    gameloop(setupfield(fieldheight,fieldwidth), snakelength, fieldheight, fieldwidth, startingposition, ui, direction, thread);
}


void singleplayerthread::run()
{

    m_ui->btnStart->setDisabled(true);
    m_ui->cbFieldsize->setDisabled(true);
    startgame(m_ui, m_direction, this, m_width);
}
