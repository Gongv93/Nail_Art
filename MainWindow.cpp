/* ========================================================================
   File:    main.cpp
   Class:   Senior Design II Csc 59867
   Creator: Asad Kamal, Vincent Gong, RuLong Haung
   ======================================================================== */

#include "MainWindow.h"

QString GroupBoxStyle = "QGroupBox {                \
                         border: 2px solid gray;    \
                         border-radius: 9px;        \
                         margin-top: 0.5em;}";

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Class Constructor
//

MainWindow::MainWindow()
{
    createWidgets();	// Create the widgets we will use
    createLayout();		// Create the window layout
    createConnections();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Class Destructor
//

MainWindow::~MainWindow() {}

void MainWindow::createWidgets()
{
    m_InputFileButton = new QPushButton("File");
    m_InputResetButton = new QPushButton("Reset");

    m_rendReset1Btn = new QPushButton("Reset");
    m_rendReset2Btn = new QPushButton("Reset");

    m_radioButton[0] = new QRadioButton ("Input");
    m_radioButton[1] = new QRadioButton ("Output");
    m_radioButton[2] = new QRadioButton ("Orthographic View");
    m_radioButton[3] = new QRadioButton ("Perspective View");

    for(int i = 0; i < 5; ++i) {
        m_filterSlider[i]  = new QSlider(Qt::Horizontal);
        m_filterSpinbox[i] = new QDoubleSpinBox;
    }
}

void MainWindow::createLayout()
{
    // Create our right coloumn
    QVBoxLayout *RightVLayout = new QVBoxLayout;
    createRightLayout(RightVLayout);

    // Create a group box for the image
    QGroupBox *groupBox = new QGroupBox();
    groupBox->setStyleSheet(GroupBoxStyle);

    // Now create our overall GUI layout
    QHBoxLayout *HorzLayout = new QHBoxLayout;
    HorzLayout->addWidget(groupBox);
    HorzLayout->setStretch(0, 1);
    HorzLayout->addLayout(RightVLayout);
    //HorzLayout->setStretchFactor(RightVLayout, 1);

    QWidget *window = new QWidget;
    window ->setLayout(HorzLayout);
    setCentralWidget(window);

}

void MainWindow::createConnections()
{
    // TODO(Vincent): Create connections with our widgets
}

void MainWindow::createRightLayout(QVBoxLayout *layout)
{
    // Create each group box
    QGroupBox *inImageBox = new QGroupBox("Input Image");
    createGroupImage(inImageBox);

    QGroupBox *imgFilterBox = new QGroupBox("Image Filter");
    createGroupFilter(imgFilterBox);

    QGroupBox *displayBox = new QGroupBox("Display");
    createGroupDisplay(displayBox);

    QGroupBox *renderBox =new QGroupBox("Render");
    createGroupRender(renderBox);

    // Add them to our vertical layout
    layout->addWidget(inImageBox);
    layout->addWidget(imgFilterBox);
    layout->addWidget(displayBox);
    layout->addWidget(renderBox);
    layout->addStretch();
}

void MainWindow::createGroupImage(QGroupBox *groupBox)
{
    QHBoxLayout *HBox = new QHBoxLayout;
    HBox->addWidget(m_InputFileButton);
    HBox->addWidget(m_InputResetButton);
    groupBox->setLayout(HBox);
}

void MainWindow::createSlider(QGridLayout* layout, int row, QString label, QSlider* slider, 
                                QDoubleSpinBox* spinBox, float lowerRange,  float upperRange, float initialVal)
{  
    QLabel *spinnerLabel = new QLabel(label);
    
    slider->setValue(initialVal);
    slider->setRange(lowerRange, upperRange);
    
    spinBox->setValue(initialVal);
    spinBox->setRange(lowerRange, upperRange);

    layout->addWidget(spinnerLabel, row, 0);
    layout->addWidget(slider, row, 1);
    layout->addWidget(spinBox, row, 2);
}

void MainWindow::createGroupFilter(QGroupBox* groupBox)
{
    QGridLayout *filterLayout = new QGridLayout;

    createSlider(filterLayout, 0, "Brightness",  m_filterSlider[0], m_filterSpinbox[0], -256, 256, 0);
    createSlider(filterLayout, 1, "Contrast",    m_filterSlider[1], m_filterSpinbox[1], -100, 100, 0);
    createSlider(filterLayout, 2, "Gamma",       m_filterSlider[2], m_filterSpinbox[2],  0.1f, 10,  5);
    createSlider(filterLayout, 3, "Sharp Size",  m_filterSlider[3], m_filterSpinbox[3],  1, 100, 50);
    createSlider(filterLayout, 4, "Sharp Fctr",  m_filterSlider[4], m_filterSpinbox[4],  1, 100, 50);

    groupBox->setLayout(filterLayout);
}

void MainWindow::createPhysDimLayout()
{
    //QGroupBox *dimensionsBox = new QGroupBox("Physical Dimensions");

    //Creating Sliders Labels
    QLabel *dimLabel[6];
    dimLabel[0] = new QLabel("Art Width");
    dimLabel[1] = new QLabel("Art Height");
    dimLabel[2] = new QLabel("Gauge");
    dimLabel[3] = new QLabel("Spacing");
    dimLabel[4] = new QLabel("Nails");
    dimLabel[5] = new QLabel("Image");


    // Need to finish this

    //return dimensionsBox;
}

void MainWindow::createGroupDisplay(QGroupBox* groupBox)
{
    QVBoxLayout *HorzBut = new QVBoxLayout;
    HorzBut -> addWidget(m_radioButton[0]);
    HorzBut -> addWidget(m_radioButton[1]);
    HorzBut -> addWidget(m_radioButton[2]);
    HorzBut -> addWidget(m_radioButton[3]);

    groupBox->setLayout(HorzBut);
}

void MainWindow::createGroupRender(QGroupBox* groupBox)
{
    //This section not complete.
    // need to add some type of display then
    // two more push buttons
    QHBoxLayout *rendHBox = new QHBoxLayout;
    rendHBox->addWidget(m_rendReset1Btn);
    rendHBox->addWidget(m_rendReset2Btn);

    groupBox->setLayout(rendHBox);
}
