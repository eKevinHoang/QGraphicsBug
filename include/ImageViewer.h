#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "MyRectItem.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QMap>
#include <QMenu>
#include <QPixmap>
#include <QPointF>
#include <QWidget>

class ImageViewer : public QGraphicsView {
    Q_OBJECT

  public:
    explicit ImageViewer(QWidget* parent = nullptr);

    bool displayImage(const QString& imageFile);
    void zoomIn();
    void zoomOut();
    void resetZoom();
    void panImage(const QPointF& delta);
    
    void undo();

  protected:
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void setupScene();
    void adjustWindowSize();

  private:
    QPixmap image;
    QGraphicsPixmapItem* imageItem;

    qreal defaultScaleFactor;

    bool isPanning = false;
    QPoint lastMousePosition;
};

#endif // IMAGEVIEWER_H
