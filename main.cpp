#include <QtWidgets>

#include "glwidget.h"
#include "objparser.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GLWidget window;
    window.resize(320, 240);
    window.show();
    window.setWindowTitle(
        QApplication::translate("frrviewer", "FRR Viewer"));
    return app.exec();
}
