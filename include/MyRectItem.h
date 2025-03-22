#ifndef ANNOTATIONITEM_H
#define ANNOTATIONITEM_H

#include <QFocusEvent>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

class MyRectItem : public QGraphicsRectItem {
  public:
    MyRectItem(const QRectF& rect, QGraphicsItem* parent = nullptr);

  protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;

  private:
};

#endif // ANNOTATIONITEM_H