#include "DemoWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Inria");
    QCoreApplication::setApplicationName("SIMageViewer demo");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    //SImageViewer2d viewer;
    //viewer.setImageFile(qApp->applicationDirPath()+QDir::separator()+"ISM_vitesse1.tif");
    //viewer.show();

    DemoWindow demoViewer;
    demoViewer.show();

    app.setStyleSheet("file:///"+qApp->applicationDirPath()+QDir::separator()+"theme"+QDir::separator()+"stylesheet.css");
    return app.exec();
}
