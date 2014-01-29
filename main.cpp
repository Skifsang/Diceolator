#include "MainWindow.h"
#include <QApplication>
#include "Dice.h"
#include "QTime"



int main(int argc, char *argv[])
{
    //Создание "семени" для рандома
    qsrand(QTime::currentTime().msec());

    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
