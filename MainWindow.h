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
	void createRightLayout(QVBoxLayout *layout);
	void createInImgLayout(QVBoxLayout *layout);
	void createImgFilLayout(QVBoxLayout *layout);
	void createPhysDimLayout(QVBoxLayout *layout);
	void createDisplayLayout(QVBoxLayout *layout);
	void createRenderLayout(QVBoxLayout *layout);

	// Private Variables	

};

#endif