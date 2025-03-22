#include "ImageViewer.h"
#include <QApplication>
#include <QFileInfo>
#include <QGraphicsPixmapItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <QWheelEvent>
#include <QWidgetAction>
#include <QtMath>

ImageViewer::ImageViewer(QWidget* parent) : QGraphicsView(parent) {
    setScene(new QGraphicsScene(this));
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
    // setResizeAnchor(QGraphicsView::AnchorViewCenter);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setBackgroundBrush(Qt::black);

    setMouseTracking(true);
    setDragMode(QGraphicsView::NoDrag);

    defaultScaleFactor = 1.2 / devicePixelRatio();
}

bool ImageViewer::displayImage(const QString& imageFile) {
    if (!image.load(imageFile)) {
        qWarning() << "Failed to load image:" << imageFile;
        return false;
    }

    window()->setWindowTitle(QString("%2").arg(QFileInfo(imageFile).fileName()));
    setupScene();
    return true;
}

void ImageViewer::zoomIn() {
    scale(1.1, 1.1);
    adjustWindowSize();
}

void ImageViewer::zoomOut() {
    scale(1 / 1.1, 1 / 1.1);
    adjustWindowSize();
}

void ImageViewer::resetZoom() {
    resetTransform();
    adjustWindowSize();
}

void ImageViewer::panImage(const QPointF& delta) { translate(delta.x(), delta.y()); }

void ImageViewer::setupScene() {
    QSizeF imageSize = image.size() * defaultScaleFactor;
    if (imageItem) {
        resetTransform();
        imageItem->setPixmap(image.scaled(imageSize.width(), imageSize.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        imageItem = scene()->addPixmap(image.scaled(imageSize.width(), imageSize.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    imageItem->setTransformationMode(Qt::SmoothTransformation);

    new MyRectItem(QRect(100, 100, 50, 60), imageItem);
    new MyRectItem(QRect(200, 100, 320, 320), imageItem);
    adjustWindowSize();
}

void ImageViewer::undo() {
    QMessageBox confirmBox;
    confirmBox.setMinimumWidth(640);
    confirmBox.setIcon(QMessageBox::Warning);
    confirmBox.setWindowTitle("Confirm Reset");
    confirmBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    confirmBox.setDefaultButton(QMessageBox::No);  // Default to "No" to prevent accidental resets
    confirmBox.setText("Are you sure you want to reset to the last saved state?");
    if (confirmBox.exec() == QMessageBox::Yes) {
        // After the user selects YES in the confirmBox, we need to perform some interaction, such as working with RectItem or showing a menu/dialog.
        // In this minimal example, we simply iterate over RectItems without modifying them.
        QList<QGraphicsItem*> sceneItems = scene()->items();
        for (QGraphicsItem* item : sceneItems) {
            if (item == imageItem) continue;
            MyRectItem* myItem = dynamic_cast<MyRectItem*>(item);
            if (myItem->rect().normalized().size() == QSizeF(1, 1)) {
                scene()->removeItem(myItem);
                delete myItem;
            }
        }
    }
}

void ImageViewer::keyPressEvent(QKeyEvent* event) {
    QGraphicsView::keyPressEvent(event);
    QPoint cursorPos = cursor().pos();
    switch (event->key()) {
    case Qt::Key_Escape:
        resetZoom();
        break;
    case Qt::Key_Delete:
    case Qt::Key_Backspace:
        break;
    case Qt::Key_A:
        break;
    case Qt::Key_S:
        break;
    case Qt::Key_Z:
        if (event->modifiers() & Qt::ControlModifier) {
            undo();
        }
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
    case Qt::Key_Return:
        break;
    default:
        break;
    }
}

void ImageViewer::wheelEvent(QWheelEvent* event) {
    QGraphicsView::wheelEvent(event);
    (event->angleDelta().y() > 0) ? zoomIn() : zoomOut();
}

void ImageViewer::mousePressEvent(QMouseEvent* event) {
    QGraphicsView::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        if (event->modifiers() & Qt::ControlModifier) {
            isPanning = true;
            lastMousePosition = event->pos();
            QGraphicsView::setTransformationAnchor(QGraphicsView::NoAnchor);
            viewport()->setCursor(Qt::ClosedHandCursor);
        }
    }
}

void ImageViewer::mouseMoveEvent(QMouseEvent* event) {
    QGraphicsView::mouseMoveEvent(event);
    QPointF scenePos = mapToScene(event->pos());
    if (isPanning && event->buttons() & Qt::LeftButton && event->modifiers() & Qt::ControlModifier) {
        QPointF delta = scenePos - mapToScene(lastMousePosition);
        panImage(delta);
        lastMousePosition = event->pos();
    }
}

void ImageViewer::mouseReleaseEvent(QMouseEvent* event) {
    QGraphicsView::mouseReleaseEvent(event);
    if (isPanning) {
        isPanning = false;
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        viewport()->unsetCursor();
    }
}

void ImageViewer::adjustWindowSize() {
    // Normally, the window size might need to be adjusted dynamically.
    // However, in this example, we always set a fixed size and do not change it.
    QSizeF screenSize = QApplication::primaryScreen()->size();
    window()->setFixedSize(screenSize.toSize());
    QSizeF windowPos = ((screenSize - window()->size()) / 2);
    window()->move(windowPos.width(), windowPos.height());
}
