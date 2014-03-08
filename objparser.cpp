#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVector3D>
#include <QGLWidget>

#include "objparser.h"

ObjParser::ObjParser()
{
    QColor c(Qt::darkGray);
    matColor[0] = c.redF();
    matColor[1] = c.greenF();
    matColor[2] = c.blueF();
    matColor[3] = c.alphaF();
}

ObjParser::~ObjParser()
{
}

void ObjParser::readObjFile(const QString &name)
{
    QVector<GLushort> currentFace;
    int faceCount = 0;
    qreal x;
    qreal y;
    qreal z;

    //    //prepare OpenGL buffers
    //    glGenVertexArrays(1, vaos);
    //    glBindVertexArray(vaos[0]);

    QFile inputFile(name);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while ( !in.atEnd() )
        {
            QString line = in.readLine();
            line = line.trimmed();

            //comment
            if(line.startsWith('#'))
            {
                qDebug() << line;
                continue;
            }

            //vertex
            if(line.startsWith('v'))
            {
                QStringList tokens = line.split(QRegExp("\\s"), QString::SkipEmptyParts);
                if(tokens.at(0) == "v")
                {
                    x = tokens.at(1).toFloat();
                    y = tokens.at(2).toFloat();
                    z = tokens.at(3).toFloat();
                    vertices.append(QVector3D(x,y,z));
                }
                else if(tokens.at(0) == "vn")
                {
                    x = tokens.at(1).toFloat();
                    y = tokens.at(2).toFloat();
                    z = tokens.at(3).toFloat();
                    normals.append(QVector3D(x,y,z));
                }
                continue;
            }

            //face
            if(line.startsWith('f'))
            {
                currentFace.clear();
                QStringList tokens = line.split(QRegExp("\\s"), QString::SkipEmptyParts);
                for(int i = 1; i<4; i++) {
                    int slashCount = tokens.at(i).count('/');
                    if(slashCount == 0) {
                        //vertex
                        currentFace.append(tokens.at(i).toInt());
                    }
                    else if(slashCount == 1) {
                        //vertex/texture-coordinate
                        QStringList values = tokens.at(i).split(QRegExp("/"), QString::SkipEmptyParts);
                        currentFace.append(values.at(0).toInt());
                    }
                    else if(slashCount == 2) {
                        QStringList values = tokens.at(i).split(QRegExp("/"), QString::SkipEmptyParts);
                        if(values.size() == 2) {
                            //vertex//normal
                            currentFace.append(values.at(0).toInt());
                        }
                        else if(values.size() == 3) {
                            //vertex/texture-coordinate/normal
                            currentFace.append(values.at(0).toInt());
                        }
                    }
                }

                //transfer current face to faces list
                for(int j = 0; j<currentFace.size(); j++)
                {
                    faces.append(currentFace.at(j) - 1);
                }
                faceCount++;
                continue;
            }
        }
    }

    //    //copy data into OpenGL vertex array buffer
    //    glGenBuffers(1, buffers);
    //    glBufferData(GL_ARRAY_BUFFER, (3 * vertices.size()) * sizeof(GLfloat), vertices.constData(), GL_STATIC_DRAW);
    //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //    glEnableVertexAttribArray(0);

    qDebug() << "Vertices: " << vertices.size();
    qDebug() << "Normals: " << normals.size();
    qDebug() << "Triangles: " << faces.size() / 3;
    qDebug() << "Faces: " << faceCount;

    inputFile.close();
}

void ObjParser::draw()
{
    glVertexPointer(3, GL_FLOAT, 0, vertices.constData());
    glNormalPointer(GL_FLOAT, 0, normals.constData());

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glColor3f(1.0, 0.5, 0.3);

    const GLushort *indices = faces.constData();
    glDrawElements(GL_TRIANGLES, faces.size(), GL_UNSIGNED_SHORT, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void convertGLColor(float colorVec[], QColor c)
{
    colorVec[0] = c.redF();
    colorVec[1] = c.greenF();
    colorVec[2] = c.blueF();
    colorVec[3] = c.alphaF();
}
