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


    // update button with filename (without path)
    m_InputFileButton->setText(f.fileName());
    m_InputFileButton->update();

	preview();

	// Return 1 on success
	return 1;
}

void MainWindow::changeThresholdD(double val)
{
    changeThresholdI((int) val);
}

// Slot to process change in threshold value caused by moving the slider.

void MainWindow::changeThresholdI(int val)
{

    m_filterSlider [0]->blockSignals(true);
    m_filterSlider [0]->setValue    (val);
    m_filterSlider [0]->blockSignals(false);
    m_filterSpinbox[0]->blockSignals(true);
    m_filterSpinbox[0]->setValue    (val);
    m_filterSpinbox[0]->blockSignals(false);


    // apply new values to stored image
    preview();
}




// Slot to reset threshold parameter
void MainWindow::reset()
{
    m_filterSlider[0]->setValue(128);

    // apply new values to stored image
    preview();
}


void MainWindow::quit()
{
    // close window
    exit(0);
}

