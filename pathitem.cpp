#include "pathitem.h"

PathItem::PathItem()
{

}

QRectF PathItem::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void PathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    painter->setPen(QPen(QColor(0, 0, 255), 1));

    painter->drawPoints(path);
}

void PathItem::SetSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

void PathItem::SetPath(vector<Point> *path)
{
    this->path.clear();

    vector<Point>::iterator itr = path->begin();
    for(;itr != path->end(); itr ++)
    {
        this->path << ( QPoint((*itr).x, (*itr).y));
    }

    update();
}
