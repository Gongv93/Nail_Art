/* ========================================================================
   File:    slots.cpp
   Class:   Senior Design II Csc 59867
   Creator: Asad Kamal, Vincent Gong, RuLong Haung
   ======================================================================== */


#include "MainWindow.h"

int MainWindow::load()
{
	QFileDialog dialog(this);

	// Open the last know working directory
	if(!m_currentDir.isEmpty())
		dialog.setDirectory(m_currentDir);

	// Display existing files and directories
	dialog.setFileMode(QFileDialog::ExistingFile);

	// Invoke native file browser to select file
	m_file = dialog.getOpenFileName(this,
									"Open File", m_currentDir,
									"Images (*.jpg *.png *.ppm *.pgm *.bmp);;All files (*)");

	// Verify that file selection was made
	if(m_file.isNull()) return 0;

	// Save the current directory
	QFileInfo f(m_file);
	m_currentDir = f.absolutePath();

	// Read input image and convert to grayscale
	m_imageSrc = IP::IP_readImage(qPrintable(m_file));
	IP_castImage(m_imageSrc, BW_IMAGE, m_imageSrc); 

    m_artWidth  = m_imageSrc->width();
    m_artHeight = m_imageSrc->height();

    // update button with filename (without path)
    m_InputFileButton->setText(f.fileName());
    m_InputFileButton->update();

	preview();

	// Return 1 on success
	return 1;
}

void MainWindow::changeComboBox(int index)
{
    // Get our value from our combo box
    float n = m_comboBox->itemData(index).toFloat();
    
    // Then convert it to a string
    QString s;
    s.setNum(n, 'g', 6);

    // Set our label
    m_labelSpacing->setText(s);
    
    preview();
}

void MainWindow::changeArtSize()
{
    preview();
}

void MainWindow::changeBrightnessD(double val)
{
    changeBrightnessI((int) val);
}

// Slot to process change in threshold value caused by moving the slider.

void MainWindow::changeBrightnessI(int val)
{
    m_filterSlider [0]->blockSignals(true);
    m_filterSlider [0]->setValue    (val);
    m_filterSlider [0]->blockSignals(false);
    m_filterSpinbox[0]->blockSignals(true);
    m_filterSpinbox[0]->setValue    (val);
    m_filterSpinbox[0]->blockSignals(false);

    m_brightness = val;

    // apply new values to stored image
    preview();
}

void MainWindow::changeContrastD(double val)
{
    changeContrastI((int) val);
}

// Slot to process change in threshold value caused by moving the slider.

void MainWindow::changeContrastI(int val)
{
    m_filterSlider [1]->blockSignals(true);
    m_filterSlider [1]->setValue    (val);
    m_filterSlider [1]->blockSignals(false);
    m_filterSpinbox[1]->blockSignals(true);
    m_filterSpinbox[1]->setValue    (val);
    m_filterSpinbox[1]->blockSignals(false);

    m_contrast = val;

    // apply new values to stored image
    preview();
}

void MainWindow::changeGammaD(double val){
	changeGammaI((int)val);	
}

void MainWindow::changeGammaI(int val)
{
	m_filterSlider [2]->blockSignals(true);
    m_filterSlider [2]->setValue    (val);
    m_filterSlider [2]->blockSignals(false);
    m_filterSpinbox[2]->blockSignals(true);
    m_filterSpinbox[2]->setValue    (val);
    m_filterSpinbox[2]->blockSignals(false);

    m_gamma = val;

    // apply new values to stored image
    preview();
}

void MainWindow::changeSharpenSizeD(double val){
	changeSharpenSizeI((int)val);	
}

void MainWindow::changeSharpenSizeI(int val)
{
	m_filterSlider [3]->blockSignals(true);
    m_filterSlider [3]->setValue    (val);
    m_filterSlider [3]->blockSignals(false);
    m_filterSpinbox[3]->blockSignals(true);
    m_filterSpinbox[3]->setValue    (val);
    m_filterSpinbox[3]->blockSignals(false);

    m_filterSize = val;

    // apply new values to stored image
    preview();
}

void MainWindow::changeSharpenFctrD(double val){
	changeSharpenFctrI((int)val);	
}

void MainWindow::changeSharpenFctrI(int val)
{
	m_filterSlider [4]->blockSignals(true);
    m_filterSlider [4]->setValue    (val);
    m_filterSlider [4]->blockSignals(false);
    m_filterSpinbox[4]->blockSignals(true);
    m_filterSpinbox[4]->setValue    (val);
    m_filterSpinbox[4]->blockSignals(false);

    m_filterFctr = val;

    // apply new values to stored image
    preview();
}

void MainWindow::displayIn   () { display(0); }
void MainWindow::displayOut  () { display(1); }

// Slot to reset threshold parameter
void MainWindow::reset()
{
    m_filterSlider[0]->setValue(128);
    
    m_brightness = 0;
    m_contrast = 1;
    m_gamma = 1;
    m_filterSize = 3;
    m_filterFctr = 3; 

    m_filterSlider[0]->setValue(m_brightness);
    m_filterSlider[1]->setValue(m_contrast);
    m_filterSlider[2]->setValue(m_gamma);
    m_filterSlider[3]->setValue(m_filterSize);
    m_filterSlider[4]->setValue(m_filterFctr);

    // apply new values to stored image
    preview();
}

void MainWindow::quit()
{
    // close window
    exit(0);
}

