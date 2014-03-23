#ifndef MESH_H
#define MESH_H

#include <QString>
#include <QMatrix4x4>
#include <QGLWidget>

class Mesh
{
public:
    Mesh();
    ~Mesh();

    void readObjFile(const QString &name);
    void draw();

    QVector3D translation;

private:
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<GLushort> faces;
    GLushort start;
    QMatrix4x4 matrix;
    GLfloat matColor[4];
    void convertGLColor(float colorVec[], QColor c);
};

#endif // MESH_H
