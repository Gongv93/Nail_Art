/* ========================================================================
   File:    main.cpp
   Class:   Senior Design II Csc 59867
   Creator: Asad Kamal, Vincent Gong, RuLong Haung
   ======================================================================== */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtWidgets>
#include <QMainWindow>


namespace UI
{
    class MainwWindow;
    class QAction;
    class QWidget;
    class QVBoxLayout;
    class QHBoxLayout;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
   ~MainWindow();

public slots:

private:
    // Private Functions
    void createLayout();

    QGroupBox*  createGroupImage();
    QGroupBox*  createGroupFilter();
    QGroupBox*  createGroupDimensions();
    QGroupBox*  createGroupDisplay();
    QGroupBox*  createGroupRender();


    // Private Member Variables
    QPushButton    *m_InputFileButton;
    QPushButton    *m_InputResetButton;
    QPushButton    *m_rendReset1Btn;
    QPushButton    *m_rendReset2Btn;


    QSlider         *m_filterSlider[5];
    QRadioButton    *m_radioButton[4];
    QDoubleSpinBox  *m_filterSpinbox[5];
    QDoubleSpinBox  *m_dimSpinbox[2];













};

#endif
