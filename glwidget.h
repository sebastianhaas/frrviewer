#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include <QOpenGLShaderProgram>
#include <QColor>
#include <QOpenGLTimerQuery>

#include "mesh.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void drawAxes();
    void drawGrid();

private:
    int xRot;
    int yRot;
    int zRot;
    bool boundingBoxesVisible;
    QColor backgroundColor;
    QPoint lastPos;
    QVector3D position;
    QOpenGLShaderProgram shaderProgram;
    QList<Mesh> meshes;
    QOpenGLTimerQuery timerQuery;
};

#endif // OPENGLWIDGET_H
