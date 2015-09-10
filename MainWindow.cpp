#include "MainWindow.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Class Constructor
//

MainWindow::MainWindow()
{
	createWidgets();	// Create the widgets we will use 
	createLayout();		// Create the window layout
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Class Destructor
//

MainWindow::~MainWindow() {}

void MainWindow::createWidgets()
{
	// TODO(Vincent): Create the widgets
}

void MainWindow::createLayout()
{
	// Create our right coloumn
	QVBoxLayout *rightCol = new QVBoxLayout;
	createRightLayout(rightCol);

	// TODO(Vincent): After creating the right coloum, add it next to the image widget
	//

}

void MainWindow::createRightLayout(QVBoxLayout *layout)
{
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


}

void MainWindow::createInImgLayout(QVBoxLayout *layout)
{
	// TODO(Vincent): Create the layout
}

void MainWindow::createImgFilLayout(QVBoxLayout *layout)
{
	// TODO(Vincent): Create the layout
}

void MainWindow::createPhysDimLayout(QVBoxLayout *layout)
{
	// TODO(Vincent): Create the layout
}

void MainWindow::createDisplayLayout(QVBoxLayout *layout)
{
	// TODO(Vincent): Create the layout
}

void MainWindow::createRenderLayout(QVBoxLayout *layout)
{
	// TODO(Vincent): Create the layout
}

