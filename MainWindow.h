/* ========================================================================
   File:    MainWindow.h
   Class:   Senior Design Csc 59866
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
	void createWidgets();

	void createLayout();
	void createRightLayout(QGroupBox *layout);
	void createInImgLayout(QGroupBox *layout);
	void createImgFilLayout(QGroupBox *layout);
	void createPhysDimLayout(QGroupBox *layout);
	void createDisplayLayout(QGroupBox *layout);
	void createRenderLayout(QGroupBox *layout);

	void createSlider()
	
	// Private Variables	
	// Variables for our Input Image section
	QPushButton *mInputFileButton;
	QPushButton *mInputResetButton;


};

#endif