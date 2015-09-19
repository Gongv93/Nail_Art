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

	preview();

	// Return 1 on success
	return 1;
}

void MainWindow::quit()
{
    // close window
    exit(0);
}

