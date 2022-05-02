#ifndef SINGLEPLAYERTHREAD_H
#define SINGLEPLAYERTHREAD_H

#include "QThread"
#include "singleplayer.h"

class singleplayerthread : public QThread
{
    Q_OBJECT

public:
    singleplayerthread(Ui::Singleplayer *ui, int *direction, int width);

protected:
    void run();

private:
    Ui::Singleplayer *m_ui;
    int *m_direction;
    int m_width;

};


#endif // SINGLEPLAYERTHREAD_H
