/* ========================================================================
   File:    main.cpp
   Class:   Senior Design II Csc 59867
   Creator: Asad Kamal, Vincent Gong, RuLong Haung
   ======================================================================== */

#include "MainWindow.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Class Constructor
//

MainWindow::MainWindow()
{
<<<<<<< HEAD
    createWidgets();	// Create the widgets we will use
=======
>>>>>>> master
    createLayout();		// Create the window layout
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Class Destructor
//

MainWindow::~MainWindow() {}

<<<<<<< HEAD
void MainWindow::createWidgets()
{
    // TODO(Vincent): Create the widgets

    mInputFileButton = new QPushButton("File");
    mInputResetButton = new QPushButton("Reset");
}

void MainWindow::createLayout()
{
    // Create our right coloumn
    QVBoxLayout *rightCol = new QVBoxLayout;
    createRightLayout(rightCol);

    // TODO(Vincent): After creating the right coloum, add it next to the image widget
}

void MainWindow::createRightLayout(QVBoxLayout *layout)
{
    // TODO(Vincent): Change the QVBoxLayout to groupboxes

    // Create the layout for Input Image
    QVBoxLayout *inputImageLayout = new QVBoxLayout;
    createInImgLayout(inputImageLayout);

    // Create the layout for Image Filter
    QVBoxLayout *imageFilterLayout = new QVBoxLayout;
    createImgFilLayout(imageFilterLayout);

    // Create the layout for Physical Dimensions
    QVBoxLayout *physicalDimensionsLayout = new QVBoxLayout;
    createPhysDimLayout(physicalDimensionsLayout);

    // Create the layout for Display
    QVBoxLayout *displayLayout = new QVBoxLayout;
    createDisplayLayout(displayLayout);

    // Create the layout for Render
    QVBoxLayout *renderLayout = new QVBoxLayout;
    createRenderLayout(renderLayout);

    // TODO(Vincent): Create the layout for the save and quit buttons on the bottom

    // TODO(Vincent): Put all layouts together to form the right coloumn
=======

void MainWindow::createLayout()
{

    QVBoxLayout *RightVLayout = new QVBoxLayout;
    RightVLayout -> addWidget(createGroupImage());
    RightVLayout -> addWidget(createGroupFilter());
    RightVLayout -> addWidget(createGroupDimensions());
    RightVLayout -> addWidget(createGroupDisplay());
    RightVLayout -> addWidget(createGroupRender());
    RightVLayout  ->addStretch();

    QHBoxLayout *HorzLayout = new QHBoxLayout;
    HorzLayout -> addLayout(RightVLayout);
    HorzLayout -> setStretchFactor(RightVLayout, 1);

    QWidget *window = new QWidget;
    window ->setLayout(HorzLayout);
    setCentralWidget(window);

}

QGroupBox* MainWindow::createGroupImage()
{
    QGroupBox *InImageBox =new QGroupBox("Input Image");

    m_InputFileButton = new QPushButton("File");
    m_InputResetButton = new QPushButton("Reset");

    QHBoxLayout *HBox = new QHBoxLayout;
    HBox ->addWidget(m_InputFileButton);
    HBox ->addWidget(m_InputResetButton);
>>>>>>> master

    InImageBox ->setLayout(HBox);

    return InImageBox ;
}

QGroupBox* MainWindow::createGroupFilter()
{
<<<<<<< HEAD
    // TODO(Vincent): Create the layout
=======
    QGroupBox *InpFilterBox = new QGroupBox("Image Filter");

    //Creating Sliders Labels
    QLabel *slidersLabel[5];
    slidersLabel[0] = new QLabel("Brightness");
    slidersLabel[1] = new QLabel("Contrast");
    slidersLabel[2] = new QLabel("Gamma");
    slidersLabel[3] = new QLabel("Sharp Size");
    slidersLabel[4] = new QLabel("Sharp Fctr");

    //Creating Sliders
    for(int i=0; i<5; i++)
    {
        m_filterSlider[i] = new QSlider(Qt::Horizontal);
        m_filterSlider[i] -> setValue(0);

        //Setting Range of Slider values
        switch(i)
        {
           case 0: m_filterSlider[i] -> setRange(-128,128);break;
           case 1: m_filterSlider[i] -> setRange(-100,100);break;
           case 2: m_filterSlider[i] -> setRange(-180,180);break;   //have to find out the range of values
           case 3: m_filterSlider[i] -> setRange(-100,100);break;   //have to find out the range of values
           case 4: m_filterSlider[i] -> setRange(-100,100);break;  // have to find out the range of values
        }
    }


    //Creating SpinBoxes
    for(int i=0; i<5; i++)
    {
        m_filterSpinbox[i] = new QDoubleSpinBox;
        m_filterSpinbox[i] -> setValue(0);

        //Setting Range of Spinbox values
        switch(i)
        {
           case 0: m_filterSpinbox[i] -> setRange(-128,128);break;
           case 1: m_filterSpinbox[i] -> setRange(-100,100);break;
           case 2: m_filterSpinbox[i] -> setRange(-180,180);break;   //have to find out the range of values have ask prof
           case 3: m_filterSpinbox[i] -> setRange(-100,100);break;   //have to find out the range of values
           case 4: m_filterSpinbox[i] -> setRange(-100,100);break;  // have to find out the range of values
        }
    }

    //Assemble Widgets in a Grid:
    QGridLayout *filterGrid = new QGridLayout;
    for(int i=0; i<5; i++)
    {
        filterGrid -> addWidget(slidersLabel[i], i, 0);
        filterGrid -> addWidget(m_filterSlider[i], i, 1);
        filterGrid -> addWidget(m_filterSpinbox[i], i, 2);
    }

    InpFilterBox->setLayout(filterGrid);

    return InpFilterBox;
>>>>>>> master
}

// Need to finish this
QGroupBox* MainWindow:: createGroupDimensions()
{
<<<<<<< HEAD
    // TODO(Vincent): Create the layout
}

void MainWindow::createPhysDimLayout(QGroupBox *layout)
{
    // TODO(Vincent): Create the layout
=======
    QGroupBox *dimensionsBox = new QGroupBox("Physical Dimensions");

    //Creating Sliders Labels
    QLabel *dimLabel[6];
    dimLabel[0] = new QLabel("Art Width");
    dimLabel[1] = new QLabel("Art Height");
    dimLabel[2] = new QLabel("Gauge");
    dimLabel[3] = new QLabel("Spacing");
    dimLabel[4] = new QLabel("Nails");
    dimLabel[5] = new QLabel("Image");


    // Need to finish this

    return dimensionsBox;
>>>>>>> master
}

QGroupBox* MainWindow::createGroupDisplay()
{
<<<<<<< HEAD
    // TODO(Vincent): Create the layout
=======
    QGroupBox *displayBox = new QGroupBox("Display");

    m_radioButton[0] = new QRadioButton ("Input");
    m_radioButton[1] = new QRadioButton ("Output");
    m_radioButton[2] = new QRadioButton ("Orthographic View");
    m_radioButton[3] = new QRadioButton ("Perspective View");

    QVBoxLayout *HorzBut = new QVBoxLayout;
    HorzBut -> addWidget(m_radioButton[0]);
    HorzBut -> addWidget(m_radioButton[1]);
    HorzBut -> addWidget(m_radioButton[2]);
    HorzBut -> addWidget(m_radioButton[3]);

    displayBox->setLayout(HorzBut);

    return displayBox;
>>>>>>> master
}

QGroupBox* MainWindow:: createGroupRender()
{
<<<<<<< HEAD
    // TODO(Vincent): Create the layout
=======

    //This section not complete.
    // need to add some type of display then
    // two more push buttons

    QGroupBox *renderBox =new QGroupBox("Render");

    m_rendReset1Btn = new QPushButton("Reset");
    m_rendReset2Btn = new QPushButton("Reset");

    QHBoxLayout *rendHBox = new QHBoxLayout;
    rendHBox ->addWidget(m_rendReset1Btn);
    rendHBox ->addWidget(m_rendReset2Btn);

    renderBox ->setLayout(rendHBox);

    return renderBox;
>>>>>>> master
}

// Vincent make the imagewindow to appear on right side
