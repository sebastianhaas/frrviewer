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
    void draw() const;
    void calculateBoundingBox();
    void setBoundingBoxVisible(bool visible);

    QVector3D translation;
    QColor boundingBoxColor;

private:
    void drawBoundingBox() const;

    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<GLushort> faces;
    GLushort start;
    QMatrix4x4 matrix;
    GLfloat matColor[4];
    QVector3D boundingMin;
    QVector3D boundingMax;
    bool isBoundingBoxVisible;
};

#endif // MESH_H
