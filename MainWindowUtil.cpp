/* ========================================================================
File:    MainWindowUtil.cpp
Class:   Senior Design II Csc 59867
Creator: Asad Kamal, Vincent Gong, RuLong Haung
======================================================================== */


#include "MainWindow.h"



void MainWindow::createGridLayout(QGridLayout* layout, int row, QString label, QSlider* slider,
	QDoubleSpinBox* spinBox, float lowerRange, float upperRange, float initialVal)
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

void MainWindow::createGridLayout(QGridLayout* Layout, int Row, QString Label, QDoubleSpinBox* SpinBox,
	 float lowerRange, float upperRange, float initialVal)
{
	QLabel *spinBoxLabel = new QLabel(Label);

	SpinBox->setValue(initialVal);
	SpinBox->setRange(lowerRange, upperRange);

	Layout->addWidget(spinBoxLabel, Row, 0);
	Layout->addWidget(SpinBox, Row, 1);

}

void MainWindow::createGridLayout(QGridLayout* Layout, int Row, QString Label, QComboBox* comboBox,
	QString unitLabel)
{
	QLabel *comboLabel = new QLabel(Label);
	QLabel *unitBoxLabel = new QLabel(unitLabel);

	comboBox->addItem("16 (Thick)", 0.23622f);
	comboBox->addItem("18 (Medium)", 0.15748f);
	comboBox->addItem("23 (Thin)", 0.11811f);

	Layout->addWidget(comboLabel, Row, 0);
	Layout->addWidget(comboBox, Row, 1);
	Layout->addWidget(unitBoxLabel, Row, 2);
}


void MainWindow::createGridLayout(QGridLayout* Layout, int Row, QString Labels, QLabel *Label2)

{
	QLabel *labels = new QLabel(Labels);

	Layout->addWidget(labels, Row, 0);
	Layout->addWidget(Label2, Row, 1);
}

bool MainWindow::applyFilter(ImagePtr I1, ImagePtr I2)
{
	double brightness, contrast, gamma, filterSize, filterFctr;
	int histo[256];
	double a = 5.0;
	double b = 6.0;
	// error checking
	if (I1.isNull()) {
		IP_printfErr("applyFilter: Missing image");
		return 0;   // failure
	}

	brightness = m_brightness;
	gamma = m_gamma;
	filterSize = m_filterSize;
	filterFctr = m_filterFctr;


	if (m_contrast >= 0) {
		contrast = m_contrast / 25 + 1;
	}
	else {
		contrast = 1 + (m_contrast / 133);
    }

	int w = m_disWidth / m_spacing;
	int h = m_disHeight / m_spacing;

	// apply filter
	IP_resize(I1, w, h, IP::TRIANGLE, I2);
	IP_contrast(I2, brightness, contrast, 128, I2);
	IP_sharpen(I2, filterSize, filterSize, filterFctr, I2);
	IP_ditherDiffuse(I2, IP::JARVIS_JUDICE_NINKE, gamma, I2);
	IP_copyImage(I2, m_imageDst);

    IP_histogram(I2, 0, histo, 256, a, b);

    m_glWidget->setVars(I2, m_spacing, m_disWidth, m_disHeight);

	QString Nails = QString("%1 Nails").arg(histo[0]);
	m_labelNails->setText(Nails);

	QString artSize = QString("%1x%2 px").arg(I2->width()).arg(I2->height());
	m_labelSize->setText(artSize);
	
	return 1;   // success
}

void MainWindow::display(int flag)
{
	// error checking
	if (m_imageSrc.isNull()) return;     // no input image
	if (m_imageDst.isNull())         // compute output image
		applyFilter(m_imageSrc, m_imageDst);

	int w, h;

	if(flag == 2 || flag == 3) {
		if(flag == 2)
			m_glWidget->setOrthoView(1);
		else
			m_glWidget->setOrthoView(0);

		m_stackWidget->setCurrentIndex(2);
		return;
	}

	// raise the appropriate widget from the stack
	m_stackWidget->setCurrentIndex(flag);

	// determine image to be displayed
	ImagePtr I;
	if (flag == 0) {
		I = m_imageSrc;
		w = m_stackWidget->width();
		h = m_stackWidget->height();
	}
	else {
		I = m_imageDst;
		w = m_dimSpinbox[0]->value() / m_comboBox->itemData(m_comboBox->currentIndex()).toFloat();
		h = m_dimSpinbox[1]->value() / m_comboBox->itemData(m_comboBox->currentIndex()).toFloat();
	}

	// convert from ImagePtr to QImage to Pixmap
	QImage q;
	IP_IPtoQImage(I, q);
	QPixmap p = QPixmap::fromImage(q.scaled(QSize(w, h), Qt::KeepAspectRatio));

	// assign pixmap to label widget for display
	QLabel *widget = (QLabel *)m_stackWidget->currentWidget();
	widget->setPixmap(p);
}

void MainWindow::preview()
{
	applyFilter(m_imageSrc, m_imageDst);

	// display requested image
	int i;
	for (i = 0; i<3; i++)
		if (m_radioButton[i]->isChecked()) break;

	switch (i) {
	case 0: displayIn(); break;
	case 1: displayOut(); break;
	case 2: displayOrtho(); break;
	case 3: displayPerspec(); break;
	}
}
