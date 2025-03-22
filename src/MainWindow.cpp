#include "MainWindow.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QCloseEvent>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    imageViewer = new ImageViewer(this);
    setWindowTitle("Image Tool");
    setMinimumSize(800, 600);

    setupLayout();
    qApp->installEventFilter(this);
}

void MainWindow::setupLayout() {
    setCentralWidget(imageViewer);
    imageViewer->displayImage("images/test_image.jpg");
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        
        switch (keyEvent->key()) {
            case Qt::Key_Right:
                return true;
            case Qt::Key_Left:
                return true;
            case Qt::Key_X:
                if (keyEvent->modifiers() & Qt::ControlModifier) {
                    return true;
                }
                break;
            case Qt::Key_C:
                if (keyEvent->modifiers() & Qt::ControlModifier) {
                    return true;
                }
                break;
            case Qt::Key_V:
                if (keyEvent->modifiers() & Qt::ControlModifier) {
                    return true;
                }
            case Qt::Key_G:
                if (keyEvent->modifiers() & Qt::ControlModifier) {
                }
                break;
            case Qt::Key_Enter:
            case Qt::Key_Return:
            case Qt::Key_Escape:
                break;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    event->accept();
}