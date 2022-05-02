#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include <QMainWindow>

namespace Ui {
class Singleplayer;
}

class Singleplayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Singleplayer(QWidget *parent = nullptr);
    ~Singleplayer();

private slots:
    void on_btnStart_clicked();
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Singleplayer *ui;
    int *direction;
    int lastdirection;
};

#endif // SINGLEPLAYER_H
