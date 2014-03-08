#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <QString>
#include <QMatrix4x4>
#include <QGLWidget>

class ObjParser
{
public:
    ObjParser();
    ~ObjParser();

    void readObjFile(const QString &name);
    void draw();

private:
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<GLushort> faces;
    GLushort start;
    QMatrix4x4 matrix;
    GLfloat matColor[4];
    void convertGLColor(float colorVec[], QColor c);
};

#endif // OBJPARSER_H
