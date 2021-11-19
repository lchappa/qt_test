///@file main.cpp
#include "fenetre.h"
#include <QtNetwork>
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fenetre w;
    w.show();
    return a.exec();
}
