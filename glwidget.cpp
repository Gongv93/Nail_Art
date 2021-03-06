/* ========================================================================
   File:    GlWidget.cpp
   Class:   Senior Design II Csc 59867
   Creator: Asad Kamal, Vincent Gong, RuLong Haung
   ======================================================================== */

#include "glwidget.h"
#include <QtGlobal>

#define INIT_DEPTH 3

using namespace IP;


// GLWidget constructor.
GLWidget::GLWidget(): QGLWidget(),m_mousePosition(0,0)
{
    // init variables
    for(int i=0; i<3; i++) {
        m_rotation [i] = 0;
        m_cameraPos[i] = 0;
    }
    m_cameraPos[2] = INIT_DEPTH;
}


// GLWidget destructor.
GLWidget::~GLWidget()
{
    glDeleteLists(m_boardList, 1);
    glDeleteLists(m_nailList,  1);
    glDeleteLists(m_nailsList, 1);
}


// Initialization routine before display loop.
void GLWidget::initializeGL()
{
    glEnable	(GL_DEPTH_TEST);
    glDepthFunc	(GL_LEQUAL);
    glClearColor	(.9, .9, .9, 1.0);
    initDisplayLists(1);
}

// Update GL scene.
void GLWidget::paintGL()
{
    // clear color and depth buffer to background values
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // reset transformation matrix to identity matrix
    glLoadIdentity();

    //defining x,y,z
    float x = m_cameraPos[0];
    float y = m_cameraPos[1];
    float z = qMax(m_cameraPos[2], 1.0f);

    // move camera to (x,y,z);
    // clip z so that it is always > 1 to be in front of nailart;
    // look straight ahead: (x,y,z) looks at (x,y,0)
    // use gluLookAt(eyeX,eyeY,eyeZ, centerX,centerY,centerZ, upX,upY,upZ)
    gluLookAt(x,y,z, x,y,0, 0,1,0);

    // bring origin back to camera position to invert translation below
    glTranslatef(x, y, 0);

    // update transformation for rotation about x-, y-, and z-axes
    glRotatef(m_rotation[0], 1, 0, 0);	//  cw rotation about x-axis
    glRotatef(m_rotation[1], 0, 1, 0);	// ccw rotation about y-axis
    glRotatef(m_rotation[2], 0, 0, 1);	// ccw rotation about z-axis

    // bring orthographic projection of camera position to the origin
    glTranslatef(-x, -y, 0);

    // draw nails
    initDisplayLists(0);
    glCallList(m_nailsList);
}


// Resize event handler.
void GLWidget::resizeGL(int w, int h)
{
    // init viewport
    glViewport(0, 0, w, h);

    // save w, h
    m_windowW = w;
    m_windowH = h;

    // aspect ratio
    double ar = (double) w / h;

    // set m_xmax, m_ymax such that aspect ratio of rendering is preserved
    if(ar < 1.0) {
        m_xmax = 1.0;
        m_ymax = 1.0 / ar;
    }
    else {
        m_xmax = 1.0 * ar;
        m_ymax = 1.0;
    }

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int m = 1.5;

    if(m_orthoView) {
    	// Set up othographic view
        glOrtho(-m*m_xmax, m*m_xmax, -m*m_ymax, m*m_ymax, -10.0, 10.0);
    } else {
        // Set up perspective projection
        gluPerspective(45, ar, 0.01, 1000);
    }

    glMatrixMode(GL_MODELVIEW);
}


// Event handler for mouse press events.
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_mousePosition = event->pos();
    QGLWidget::mousePressEvent(event);
}


// Event handler for mouse release events.
void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QGLWidget::mouseReleaseEvent(event);
}


// Event handler for mouse move events.
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    Qt::KeyboardModifiers km = qApp->keyboardModifiers();

    if(event->buttons()&Qt::LeftButton || event->buttons()&Qt::MidButton) {
        QPoint pos = event->pos();
        int dx = pos.x() - m_mousePosition.x();
        int dy = pos.y() - m_mousePosition.y();

        if(event->buttons() & Qt::LeftButton) {
            m_rotation[0] += dy *.5;
            m_rotation[1] += dx *.5;
        } else if(km & Qt::ControlModifier) {
            m_cameraPos[0] -= dx * .001;
            m_cameraPos[1] += dy * .001;
        } else	m_cameraPos[2] += dy * .1;
        m_mousePosition = pos;
        updateGL();
    }

    QGLWidget::mouseMoveEvent(event);
}


// Init display lists.
void GLWidget::initDisplayLists(int flag)
{
    // create display list for board and single nail; only call it first time (flag=1)
    if(flag) {
        // draw board
        m_boardList = glGenLists(1);
        glNewList(m_boardList, GL_COMPILE);

        // compute aspect ratio
        float ar = (float) m_artWidth / m_artHeight;


        if(m_artWidth > m_artHeight)
            drawBoard(2, 2/ar, .05);
        else	drawBoard(2*ar, 2, .05);
        glEndList();

        // draw single nail
        m_nailList = glGenLists(1);
        glNewList(m_nailList, GL_COMPILE);
        drawCylinder((.04016/2), .75);
        glEndList();
    }

    // create display list for the nails
    m_nailsList = glGenLists(1);
    glNewList(m_nailsList, GL_COMPILE);
    glCallList(m_boardList);
    drawNails();
    glEndList();
}


// Draw 3D board.
void GLWidget::drawBoard(float w, float h, float d)
{
    // board is drawn from -w to w, -h to h, and -d to d
    w /= 2;
    h /= 2;

    // set the color to white
    glColor3f(1.0, 1.0, 1.0);

    // draw six quadrilaterals for six sides of the board
    glBegin(GL_QUADS);

        // Front Side
        glVertex3f( w,  h,  0);   //Front Side= Top Right Corner
        glVertex3f(-w,  h,  0);   //Front Side= Top Left  Corner
        glVertex3f(-w, -h,  0);   //Front Side= Btm Left  Corner
        glVertex3f( w, -h,  0);   //Front Side= Btm Right Corner

        // Back Side
        glVertex3f( w,  h, -d);   //Back Side= Top Right Corner
        glVertex3f(-w,  h, -d);   //Back Side= Top Left  Corner
        glVertex3f(-w, -h, -d);   //Back Side= Btm Left  Corner
        glVertex3f( w, -h, -d);   //Back Side= Btm Right Corner

        // set the color to gray
        glColor3f(0.5, 0.5, 0.5);

        // Right side
        glVertex3f( w,  h, -d);   //Right Side= Top Right Corner
        glVertex3f( w,  h,  0);   //Right Side= Top Left  Corner
        glVertex3f( w, -h,  0);   //Right Side= Btm Left  Corner
        glVertex3f( w, -h, -d);   //Right Side= Btm Right Corner

        // Left Side
        glVertex3f(-w,  h, -d);   //Left Side= Top Right Corner
        glVertex3f(-w,  h,  0);   //Left Side= Top Left  Corner
        glVertex3f(-w, -h,  0);   //Left Side= Btm Left  Corner
        glVertex3f(-w, -h, -d);   //Left Side= Btm Right Corner

        // Top Side
        glVertex3f( w,  h, -d);   //Top Side= Top Right Corner
        glVertex3f(-w,  h, -d);   //Top Side= Top Left  Corner
        glVertex3f(-w,  h,  0);   //Top Side= Btm Left  Corner
        glVertex3f( w,  h,  0);   //Top Side= Btm Right Corner

        // bottom
        glVertex3f( w, -h, -d);   //Btm Side= Top Right Corner
        glVertex3f(-w, -h, -d);   //Btm Side= Top Left  Corner
        glVertex3f(-w, -h,  0);   //Btm Side= Btm Left  Corner
        glVertex3f( w, -h,  0);   //Btm Side= Btm Right Corner

    glEnd();
}

// Draw 3D cylinder.
void GLWidget::drawCylinder(float r, float h)
{
    float degToRad = M_PI / 180.;

    // set the color to black
    glColor3f(0.0, 0.0, 0.0);

    // cylinder top at z = h (front)
    glBegin(GL_POLYGON);		// start drawing the cylinder top
    for(int i=0; i<=360; i+=5) {
        float a = i * degToRad;	// convert to radians
        glVertex3f(r*cos(a), r*sin(a), h);
    }
    glEnd();

    // cylinder bottom at z = 0 (rear)
    glBegin(GL_POLYGON);		// start drawing the cylinder bottom
    for(int i=0; i<=360; i+=5) {
        float a = i * degToRad;	// convert to radians
        glVertex3f(r*cos(a), r*sin(a), 0);
    }
    glEnd();

    // cylinder sides
    glBegin(GL_QUAD_STRIP);		// start drawing the cylinder sides
    for(int i=0; i<=360; i+=5) {
        float a = i * degToRad;	// convert to radians
        glVertex3f(r*cos(a), r*sin(a), 0);
        glVertex3f(r*cos(a), r*sin(a), h);
    }
    glEnd();
}

// Draw 3D nails.
void GLWidget::drawNails()
{
    ImagePtr I = m_image;

    // get nail spacing, and art dimension values
	double dx = m_spacing;
	double dy = dx;
	double xMax, yMax;

	float ar = m_artWidth / m_artHeight;

	if(ar < 1.0) {
        xMax = 1.0;
        yMax = 1.0 / ar;
    }
    else {
        xMax = 1.0 * ar;
        yMax = 1.0;
    }

    // compute scale factor that relates art dimensions and board coordinates
    double s1 = (2*xMax)/m_artWidth;
    double s2 = (2*yMax)/m_artHeight;

    double s  = MIN(s1,s2);

    glPushMatrix();

    if(ar > 1) {
        glTranslatef(-1, 1 / ar, 0);
        glScalef(s/ar, s/ar, s);
    }
    else {
        glTranslatef(-ar, 1, 0);
        glScalef(s*ar, s*ar, s);
    }


    // draw array of scaled cylinders
    int type;
    IP::ChannelPtr<uchar> p1;
    IP::IP_getChannel(I, 0, p1, type);
    int w = I->width ();
    int h = I->height();
    for(int y=0; y<h; y++) {
        glPushMatrix();
        // draw cylinders only where black pixels are found in row
		for (int x = 0; x < w;x++,p1++) {
			if (!*p1) glCallList(m_nailList);
			glTranslatef(dx,0,0);
		}
		glPopMatrix();
        glTranslatef(0.0, -dy, 0.0);
    }
    glPopMatrix();
}


// Reset parameters.
void GLWidget::reset()
{
    // reset variables
    for(int i=0; i<3; i++) {
        m_rotation [i] = 0;
        m_cameraPos[i] = 0;
    }
    m_cameraPos[2] = INIT_DEPTH;
    updateGL();
}


// Set flag for orthographic viewing.
void GLWidget::setOrthoView(int flag)
{
    m_orthoView = flag;
    resizeGL(m_windowW, m_windowH);
    updateGL();
}

void GLWidget::setVars(ImagePtr I, double spacing, double artWidth, double artHeight)
{
	m_image = I;
	m_spacing = spacing;
	m_artHeight = artHeight;
	m_artWidth = artWidth;
}
