#ifndef PATHITEM_H
#define PATHITEM_H

#include <QGraphicsItem>
#include <astar.h>
#include <QPainter>
#include <QPolygon>

class PathItem  : public QGraphicsItem
{
public:
    PathItem();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;

    void SetSize(int width, int height);
    void SetPath(vector<Point>* path);

private:
    int width;
    int height;

    QPolygon path;
};

#endif // PATHITEM_H
