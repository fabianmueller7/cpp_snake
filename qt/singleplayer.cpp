#include "singleplayer.h"
#include "ui_singleplayer.h"
#include <iostream>
#include<windows.h>
#include <conio.h>
#include<thread>
#include <QKeyEvent>
#include <QApplication>
#include "singleplayerthread.h"
#include <string.h>

using namespace std;

Singleplayer::Singleplayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Singleplayer)
{
    ui->setupUi(this);

    int height = 10;
    int width = 10;

}

Singleplayer::~Singleplayer()
{
    delete ui;

}



void Singleplayer::on_btnStart_clicked()
{

  std::string addrWithMask(ui->cbFieldsize->currentText().toStdString());
  std::size_t pos = addrWithMask.find("x");
  int width = stoi(addrWithMask.substr(0,pos));

  ui->tableWidget->setColumnCount(width);
  ui->tableWidget->setRowCount(width);
  ui->tableWidget->setFixedWidth(490);
  ui->tableWidget->setFixedHeight(490);
  ui->tableWidget->setShowGrid(false);
  ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

  QHeaderView *verticalHeader = ui->tableWidget->verticalHeader();
  verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
  verticalHeader->setDefaultSectionSize(490/width);

  QHeaderView *horizontalHeader = ui->tableWidget->horizontalHeader();
  horizontalHeader->setSectionResizeMode(QHeaderView::Fixed);
  horizontalHeader->setDefaultSectionSize(490/width);

  for (int h = 0; h < width; h++)
  {
      for (int w = 0; w < width; w++)
      {
          QTableWidgetItem *item =  new QTableWidgetItem("");
          item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
          ui->tableWidget->setItem(w,h,item);
      }
  }

  *direction = 6;
  singleplayerthread *thread = new singleplayerthread(ui, direction, width);
     thread->start();

}

void Singleplayer::keyPressEvent(QKeyEvent *event)
{
    //up
    if(event->key() == Qt::Key_Up)
    {
        *direction = 5; //Bits 0101
        lastdirection = 5;
    }
    //down
    else if(event->key() == Qt::Key_Down)
    {
        *direction = 9; //Bits 1001
        lastdirection = 9;
    }
    //left
    else if(event->key() == Qt::Key_Left)
    {
        *direction = 6; //Bits 0110
        lastdirection = 6;
    }
    //right
    else if(event->key() == Qt::Key_Right)
    {
        *direction = 10; //Bits 1010
        lastdirection = 10;
    }
}




