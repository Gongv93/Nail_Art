/* ========================================================================
   File:    change.cpp
   Class:   Senior Design II Csc 59867
   Creator: Asad Kamal, Vincent Gong, RuLong Haung
   ======================================================================== */

#include "MainWindow.h"

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
