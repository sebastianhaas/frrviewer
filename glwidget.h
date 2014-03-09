#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include <QColor>

#include "objparser.h"

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
    void drawAxes();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    int xRot;
    int yRot;
    int zRot;
    QColor backgroundColor;
    ObjParser objParser;
    QPoint lastPos;
    QVector3D position;
};

#endif // OPENGLWIDGET_H
