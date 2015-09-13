/* ========================================================================
   File:    main.cpp
   Class:   Senior Design Csc 59866
   Creator: Asad Kamal, Vincent Gong, RuLong Haung
   ======================================================================== */

#include "MainWindow.h"
#include <QtWidgets>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    // NOTE(Vincent): We need to find out the actual window size
    window.resize(900,750);
    window.show();

    return app.exec();
}