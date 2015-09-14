/* ========================================================================
   File:    main.cpp
   Class:   Senior Design II Csc 59867
   Creator: Asad Kamal, Vincent Gong, RuLong Haung
   ======================================================================== */

#include "Mainwindow.h"
#include <QtWidgets>
#include <QApplication>


#include <QtWidgets>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    // NOTE(Vincent): We need to find out the actual window size
    window.resize(1200,700);
    window.show();

    return app.exec();
}
