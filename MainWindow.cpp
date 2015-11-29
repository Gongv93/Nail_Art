/* ========================================================================
File:    mainwindow.cpp
Class:   Senior Design II Csc 59867
Creator: Asad Kamal, Vincent Gong, RuLong Haung
======================================================================== */

#include "MainWindow.h"

QString GroupBoxStyle = "QGroupBox {               \
						border: 2px solid gray;    \
						border-radius: 9px;        \
						margin-top: 0.5em;}";


int DefaultDisplay = 1;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Class Constructor
//

MainWindow::MainWindow()
{
	applyDefaultFilter();
	createWidgets();	// Create the widgets we will use
	createLayout();		// Create the window layout
	createConnections();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Class Destructor
//

MainWindow::~MainWindow() {}

void MainWindow::applyDefaultFilter()
{
	m_brightness = 0;
	m_contrast = 1;
	m_gamma = 1;
	m_filterSize = 3;
	m_filterFctr = 3;
	m_disHeight = 16;
	m_disWidth = 16;
	m_spacing = 0.23622;
}

void MainWindow::createWidgets()
{
	m_InputFileButton = new QPushButton("File");
	m_InputResetButton = new QPushButton("Reset");

	m_rendReset1Btn = new QPushButton("Reset");
	m_rendReset2Btn = new QPushButton("Reset");

	m_saveButton = new QPushButton("Save");
	m_quitButton = new QPushButton("Quit");

	m_radioButton[0] = new QRadioButton("Input");
	m_radioButton[1] = new QRadioButton("Output");
	m_radioButton[2] = new QRadioButton("Orthographic View");
	m_radioButton[3] = new QRadioButton("Perspective View");

	m_labelNails = new QLabel("");
	m_labelSize = new QLabel("");
	m_labelSpacing = new QLabel("0.15748");

	m_dimSpinbox[0] = new QDoubleSpinBox;
	m_dimSpinbox[1] = new QDoubleSpinBox;

	m_stackWidget = new QStackedWidget;

	m_comboBox = new QComboBox;

	m_glWidget = new GLWidget;

	for (int i = 0; i < 5; ++i)
	{
		m_filterSlider[i] = new QSlider(Qt::Horizontal);
		m_filterSpinbox[i] = new QDoubleSpinBox;
	}
}

void MainWindow::createLayout()
{
	// Create our right coloumn
	QVBoxLayout *RightVLayout = new QVBoxLayout;
	createRightLayout(RightVLayout);

	// Create a group box for the image
	QGroupBox *viewLayout = new QGroupBox();
	createGroupView(viewLayout);

	// Now create our overall GUI layout
	QHBoxLayout *HorzLayout = new QHBoxLayout;
	HorzLayout->addWidget(viewLayout);
	HorzLayout->setStretch(0, 1);
	HorzLayout->addLayout(RightVLayout);
	//HorzLayout->setStretchFactor(RightVLayout, 1);

	QWidget *window = new QWidget;
	window->setLayout(HorzLayout);
	setCentralWidget(window);
}

void MainWindow::createConnections()
{
	connect(m_InputFileButton, SIGNAL(clicked()), this, SLOT(load()));
	connect(m_quitButton, SIGNAL(clicked()), this, SLOT(quit()));
	connect(m_InputResetButton, SIGNAL(clicked()), this, SLOT(reset()));
	connect(m_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeComboBox(int)));

	connect(m_dimSpinbox[0], SIGNAL(valueChanged(double)), this, SLOT(changeArtWidth(double)));
	connect(m_dimSpinbox[1], SIGNAL(valueChanged(double)), this, SLOT(changeArtHeight(double)));
	
	connect(m_radioButton[0], SIGNAL(clicked()), this, SLOT(displayIn()));
	connect(m_radioButton[1], SIGNAL(clicked()), this, SLOT(displayOut()));
	connect(m_radioButton[2], SIGNAL(clicked()), this, SLOT(displayOrtho()));
	connect(m_radioButton[3], SIGNAL(clicked()), this, SLOT(displayPerspec()));

	connect(m_filterSlider[0], SIGNAL(valueChanged(int)), this, SLOT(changeBrightnessI(int)));
	connect(m_filterSpinbox[0], SIGNAL(valueChanged(double)), this, SLOT(changeBrightnessD(double)));

	connect(m_filterSlider[1], SIGNAL(valueChanged(int)), this, SLOT(changeContrastI(int)));
	connect(m_filterSpinbox[1], SIGNAL(valueChanged(double)), this, SLOT(changeContrastD(double)));

	connect(m_filterSlider[2], SIGNAL(valueChanged(int)), this, SLOT(changeGammaI(int)));
	connect(m_filterSpinbox[2], SIGNAL(valueChanged(double)), this, SLOT(changeGammaD(double)));

	connect(m_filterSlider[3], SIGNAL(valueChanged(int)), this, SLOT(changeSharpenSizeI(int)));
	connect(m_filterSpinbox[3], SIGNAL(valueChanged(double)), this, SLOT(changeSharpenSizeD(double)));

	connect(m_filterSlider[4], SIGNAL(valueChanged(int)), this, SLOT(changeSharpenFctrI(int)));
	connect(m_filterSpinbox[4], SIGNAL(valueChanged(double)), this, SLOT(changeSharpenFctrD(double)));
}

void MainWindow::createRightLayout(QVBoxLayout *layout)
{
	// Create each group box
	QGroupBox *inImageBox = new QGroupBox("Input Image");
	createGroupImage(inImageBox);

	QGroupBox *imgFilterBox = new QGroupBox("Image Filter");
	createGroupFilter(imgFilterBox);

	QGroupBox *physDimBox = new QGroupBox("Physical Dimensions");
	createGroupPhysDim(physDimBox);

	QGroupBox *displayBox = new QGroupBox("Display");
	createGroupDisplay(displayBox);

	QGroupBox *renderBox = new QGroupBox("Render");
	createGroupRender(renderBox);

	// Create save and exit buttons on the bottom
	QHBoxLayout *quitButtons = new QHBoxLayout;
	quitButtons->addWidget(m_saveButton);
	quitButtons->addWidget(m_quitButton);

	// Add them to our vertical layout
	layout->addWidget(inImageBox);
	layout->addWidget(imgFilterBox);
	layout->addWidget(physDimBox);
	layout->addWidget(displayBox);
	layout->addWidget(renderBox);
	layout->addStretch();
	layout->addLayout(quitButtons);
}

void MainWindow::createGroupView(QGroupBox *groupBox)
{
	groupBox->setStyleSheet(GroupBoxStyle);

	for (int i = 0; i < 2; ++i)
		m_stackWidget->addWidget(new QLabel);

	QLabel *label;
	label = (QLabel *)m_stackWidget->widget(0); label->setAlignment(Qt::AlignCenter);
	label = (QLabel *)m_stackWidget->widget(1); label->setAlignment(Qt::AlignCenter);



	m_stackWidget->addWidget(m_glWidget);

	m_stackWidget->setCurrentIndex(DefaultDisplay);


	// assemble stacked widget in vertical layout
	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addWidget(m_stackWidget);
	groupBox->setLayout(vbox);
}

void MainWindow::createGroupImage(QGroupBox *groupBox)
{
	QHBoxLayout *HBox = new QHBoxLayout;
	HBox->addWidget(m_InputFileButton);
	HBox->addWidget(m_InputResetButton);
	groupBox->setLayout(HBox);
}

void MainWindow::createGroupFilter(QGroupBox* groupBox)
{
	QGridLayout *filterLayout = new QGridLayout;

	createGridLayout(filterLayout, 0, "Brightness", m_filterSlider[0], m_filterSpinbox[0], -256, 256, 0);
	createGridLayout(filterLayout, 1, "Contrast", m_filterSlider[1], m_filterSpinbox[1], -100, 100, 0);
	createGridLayout(filterLayout, 2, "Gamma", m_filterSlider[2], m_filterSpinbox[2], 0.1f, 10, 1);
	createGridLayout(filterLayout, 3, "Sharp Size", m_filterSlider[3], m_filterSpinbox[3], 1, 100, 3);
	createGridLayout(filterLayout, 4, "Sharp Fctr", m_filterSlider[4], m_filterSpinbox[4], 1, 100, 3);

	groupBox->setLayout(filterLayout);
}

void MainWindow::createGroupPhysDim(QGroupBox* groupBox)
{

	QGridLayout *phyDimLayout = new QGridLayout;

	createGridLayout(phyDimLayout, 0, "Art Width", m_dimSpinbox[0], -256, 256, 16.00);
	createGridLayout(phyDimLayout, 1, "Art Height", m_dimSpinbox[1], -100, 100, 16.00);
	createGridLayout(phyDimLayout, 2, "Gauge", m_comboBox, "");

	createGridLayout(phyDimLayout, 3, "Spacing:", m_labelSpacing);
	createGridLayout(phyDimLayout, 4, "Nails:", m_labelNails);
	createGridLayout(phyDimLayout, 5, "Image:", m_labelSize);

	groupBox->setLayout(phyDimLayout);
}

void MainWindow::createGroupDisplay(QGroupBox* groupBox)
{
	QVBoxLayout *HorzBut = new QVBoxLayout;
	HorzBut->addWidget(m_radioButton[0]);
	HorzBut->addWidget(m_radioButton[1]);
	HorzBut->addWidget(m_radioButton[2]);
	HorzBut->addWidget(m_radioButton[3]);

	m_radioButton[DefaultDisplay]->setChecked(true);

	groupBox->setLayout(HorzBut);
}

void MainWindow::createGroupRender(QGroupBox* groupBox)
{
	QHBoxLayout *rendHBox = new QHBoxLayout;
	rendHBox->addWidget(m_rendReset1Btn);
	rendHBox->addWidget(m_rendReset2Btn);

	groupBox->setLayout(rendHBox);
}
