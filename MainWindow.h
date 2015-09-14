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
    void createWidgets();                           // Creates our widgets
    void createLayout();                            // Creates the GUI layout
    void createConnections();                       // Create connections for our widgets
    void createPhysDimLayout();

    void createRightLayout(QVBoxLayout *layout);    // Creates our right coloumn   
    void createGroupImage(QGroupBox* groupBox);     // Creates group box for image input
    void createGroupFilter(QGroupBox* groupBox);    // Creates group box for image filter
    void createGroupDisplay(QGroupBox* groupBox);   // Creates group box for display
    void createGroupRender(QGroupBox* groupBox);    // Creates group box for renderer 


    void createSlider(QGridLayout* layout, int row, QString label, QSlider* slider, 
                        QDoubleSpinBox* spinBox, float lowerRange, float upperRange, float initialVal);   // Creates our slider with a spinner and label

    // Private Variables
    // Variables for our Input Image section

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
