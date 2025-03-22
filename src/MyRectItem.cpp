#include "MyRectItem.h"
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsView>

MyRectItem::MyRectItem(const QRectF& rect, QGraphicsItem* parent): QGraphicsRectItem(rect, parent) {
    setFlag(QGraphicsItem::ItemIgnoresParentOpacity);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

void MyRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QPen currentPen = this->pen();
    QGraphicsView* view = scene()->views().first();
    qreal scaleFactor = view->transform().m11();
    qreal penWidth = qMax(0.5, qMin(2.0, currentPen.width() / scaleFactor));
    currentPen.setWidthF(penWidth);
    painter->setPen(currentPen);
    this->setPen(currentPen);
    if (hasFocus()) {
        int baseFontSize = 10;
        QFont font = painter->font();
        qreal fontSize = qMax(8.0, qMin(14.0, baseFontSize / scaleFactor));
        font.setPointSizeF(fontSize);
        painter->setFont(font);

        QString annotLabel = QString("ID: Name");
        QString elidedLabel = QFontMetrics(font).elidedText(annotLabel, Qt::ElideRight, rect().width());
        painter->drawText(rect().topLeft() - QPointF(2, 2), elidedLabel);
    }
    QGraphicsRectItem::paint(painter, option, widget);
}

void MyRectItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsRectItem::mousePressEvent(event);
    setCursor(Qt::OpenHandCursor);
}

void MyRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsRectItem::mouseMoveEvent(event);
}

void MyRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event) {
    QGraphicsRectItem::hoverMoveEvent(event);
    QRectF r = boundingRect();
    QPointF cursorPos = event->pos();
    const float margin = r.contains(cursorPos) ? 2.0 : 0.0;

    int dir = 0;
    if (qAbs(cursorPos.x() - r.left()) < margin) dir |= 1;
    if (qAbs(cursorPos.x() - r.right()) < margin) dir |= 2;
    if (qAbs(cursorPos.y() - r.top()) < margin) dir = 4;
    if (qAbs(cursorPos.y() - r.bottom()) < margin) dir = 8;

    switch (dir) {
    case 1:
    case 2:
        setCursor(Qt::SizeHorCursor);
        break;
    case 4:
    case 8:
        setCursor(Qt::SizeVerCursor);
        break;
    case (1|4):
    case (2|8):
        setCursor(Qt::SizeFDiagCursor);
        break;
    case (2|4):
    case (1|8):
        setCursor(Qt::SizeBDiagCursor);
        break;
    default:
        unsetCursor();
        break;
    }
}

void MyRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    setFlag(QGraphicsItem::ItemIsMovable, true);
    QGraphicsRectItem::mouseReleaseEvent(event);
}