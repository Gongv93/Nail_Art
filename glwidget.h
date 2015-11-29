/* ========================================================================
File:    glwidget.h
Class:   Senior Design II Csc 59867
Creator: Asad Kamal, Vincent Gong, RuLong Haung
======================================================================== */


#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>
#include <GL/glu.h>
#include "IP.h"
#include "IPtoUI.h"

using namespace IP;

class GLWidget : public QGLWidget {
    Q_OBJECT

public:
    // constructor
    GLWidget	();

    // destructor
    ~GLWidget	();

    void		setOrthoView	  (int);
    void		initDisplayLists  (int);
    void        setVars(ImagePtr I, double spacing, double artWidth, double artHeight);

public slots:
    void		reset		  ();

protected:
    void		initializeGL();       // initialize GL state
    void		paintGL();            // render GL scene
    void		resizeGL(int, int);  // resize the widget
    void		mousePressEvent(QMouseEvent *);
    void		mouseMoveEvent(QMouseEvent *);
    void		mouseReleaseEvent(QMouseEvent *);
    void		drawBoard(float, float, float);
    void		drawCylinder(float, float);
    void		drawNails();

private:
    int         m_windowW;
    int         m_windowH;
    float		m_xmax;
    float		m_ymax;
    GLuint		m_boardList;
    GLuint		m_nailList;
    GLuint		m_nailsList;
    QPoint		m_mousePosition;
    bool		m_orthoView;
    float		m_rotation [3];
    float		m_cameraPos[3];

    ImagePtr    m_image;
    double      m_spacing;
    double      m_artWidth;
    double      m_artHeight;
};

#endif // GLWIDGET_H
