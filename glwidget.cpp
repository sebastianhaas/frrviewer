#include <QDateTime>
#include <QKeyEvent>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>

#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    backgroundColor = QColor::fromRgb(235.0, 235.0, 235.0);
    position = QVector3D(0.0, 0.0, -20.0);
    xRot = 0;
    yRot = 0;
    zRot = 0;
    //objParser.readObjFile("C:/Users/Sebastian/Documents/3dsMax/export/toureffeil.obj");
    Mesh mesh = Mesh();
    mesh.readObjFile("C:/Users/Sebastian/Desktop/capsule.obj");
    mesh.translation = QVector3D(2, 0, -2);
    meshes.append(mesh);

    mesh = Mesh();
    mesh.readObjFile("C:/Users/Sebastian/Desktop/cube.obj");
    mesh.translation = QVector3D(10, 0, 10);
    meshes.append(mesh);
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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    vertexShader.compileSourceFile("C:/Users/Sebastian/Desktop/toon.vert");
    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
    fragmentShader.compileSourceFile("C:/Users/Sebastian/Desktop/toon.frag");
    shaderProgram.addShader(&vertexShader);
    shaderProgram.addShader(&fragmentShader);
    shaderProgram.link();
    shaderProgram.bind();
}

void GLWidget::paintGL()
{
    //delete color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(position.x(), position.y(), position.z());
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    //applyCamera();

    drawAxes();
    drawGrid();

    // draw meshes
    for(int i=0; i<meshes.size(); i++) {
        Mesh m = meshes.at(i);
        m.draw();
    }
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    /* create viewing cone with near and far clipping planes */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum( -1.0, 1.0, -1.0, 1.0, 1.0, 100.0);

    glMatrixMode( GL_MODELVIEW );
}

void GLWidget::drawGrid()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    for(int i=-10;i<=10;i++) {
        if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
        glVertex3f(i,0,-10);
        glVertex3f(i,0,10);
        if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
        glVertex3f(-10,0,i);
        glVertex3f(10,0,i);
    };
    glEnd();
    glEnable(GL_LIGHTING);
}

void GLWidget::drawAxes()
{
    float L = 20;
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(L,0,0); // X
    glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,L,0); // Y
    glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,L); // Z
    glEnd();
    glEnable(GL_LIGHTING);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot - 8 * dy);
        setZRotation(zRot - 8 * dx);
    }
    lastPos = event->pos();
}

static void normalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        updateGL();
    }
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    float speed = 0.3;
    QVector3D direction = QVector3D(0.0, 0.0, 1.0);
    QVector3D right = QVector3D(1.0 ,0.0, 0.0);

    // Move forward
    if (event->key() == Qt::Key_W){
        position += direction * speed;
    }
    // Move backward
    if (event->key() == Qt::Key_S){
        position -= direction * speed;
    }
    // Strafe right
    if (event->key() == Qt::Key_D){
        position -= right * speed;
    }
    // Strafe left
    if(event->key() == Qt::Key_A) {
        position += right * speed;
    }

    updateGL();
}
