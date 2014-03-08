#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    backgroundColor = QColor::fromRgb(235.0, 235.0, 235.0);
    objParser.readObjFile("C:/Users/Sebastian/Desktop/capsule.obj");
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
    qglClearColor(backgroundColor);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    //    glEnable(GL_LIGHTING);
    //    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    //    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    //    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLWidget::paintGL()
{
    //delete color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-20.0f); //move along z-axis
    //        glRotatef(30.0,0.0,1.0,0.0); //rotate 30 degress around y-axis
    //        glRotatef(15.0,1.0,0.0,0.0); //rotate 15 degress around x-axis

    objParser.draw();
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    /* create viewing cone with near and far clipping planes */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum( -1.0, 1.0, -1.0, 1.0, 5.0, 30.0);

    glMatrixMode( GL_MODELVIEW );
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
}
