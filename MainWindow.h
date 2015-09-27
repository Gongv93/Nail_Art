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

#include "IP.h"
#include "IPtoUI.h"

using namespace IP;

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
    // Slots.cpp
    int  load();
    void reset();
    void displayIn  ();
    void displayOut ();
    void changeBrightnessI(int);
    void changeBrightnessD(double);
    void changeContrastI(int);
    void changeContrastD(double);

protected slots:
    void quit();

private:
    // Variables
    QString        m_file;
    QString        m_currentDir;

    // image pointers
    ImagePtr       m_imageSrc;
    ImagePtr       m_imageDst;

    // Widgets
    QSlider         *m_filterSlider[5];
    QRadioButton    *m_radioButton[4];
    QDoubleSpinBox  *m_filterSpinbox[5];
    QDoubleSpinBox  *m_dimSpinbox[2];
    QDoubleSpinBox  *m_widthSpinbox;
    QDoubleSpinBox  *m_heightSpinbox;

    QPushButton    *m_InputFileButton;
    QPushButton    *m_InputResetButton;
    QPushButton    *m_rendReset1Btn;
    QPushButton    *m_rendReset2Btn;
    QPushButton    *m_saveButton;
    QPushButton    *m_quitButton;

    QStackedWidget *m_stackWidget;
    QComboBox* m_comboBox;

    // Filter variables
    double m_brightness;
    double m_contrast;


    // Functions
    // MainWindow.cpp
    void applyDefaultFilter();                      // Sets our filter variables
    void createWidgets();                           // Creates our widgets
    void createLayout();                            // Creates the GUI layout
    void createConnections();                       // Create connections for our widgets

    void createRightLayout(QVBoxLayout *layout);    // Creates our right coloumn

    void createGroupImage(QGroupBox* groupBox);     // Creates group box for image input
    void createGroupFilter(QGroupBox* groupBox);    // Creates group box for image filter
    void createGroupPhysDim(QGroupBox* groupBox);   // Creates group box for physical dimension
    void createGroupDisplay(QGroupBox* groupBox);   // Creates group box for display
    void createGroupRender(QGroupBox* groupBox);    // Creates group box for renderer
    void createGroupView(QGroupBox *groupBox);

    // MainWindowUtil.cpp
    void preview();
    void display(int);
    bool applyFilter(ImagePtr, ImagePtr);

    void createGridLayout(QGridLayout* layout, int row, QString label, QSlider* slider,
                            QDoubleSpinBox* spinBox, float lowerRange, float upperRange, float initialVal);   // Creates our slider with a spinner and label

    void createGridLayout(QGridLayout* Layout, int Row, QString Label, QDoubleSpinBox* SpinBox,
                            QString unitLabel, float lowerRange,  float upperRange, float initialVal);

    void createGridLayout(QGridLayout* Layout, int Row, QString Label, QComboBox* comboBox,
                            QString unitLabel);

    void createGridLayout(QGridLayout* Layout, int Row, QString Labels, QString Label2);
};

#endif
