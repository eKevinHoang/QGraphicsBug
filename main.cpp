#include "MainWindow.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("QGraphicsBug");

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
