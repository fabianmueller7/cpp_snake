#include "menu.h"
#include "ui_menu.h"
#include "singleplayer.h"
#include <QtWidgets>

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}


void Menu::on_btnScreate_clicked()
{
    Singleplayer *newSingelplayergame = new Singleplayer(new QWidget);
    newSingelplayergame->show();
}

