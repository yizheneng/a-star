#include "graphicsdisplayicon.h"

GraphicsDisplayIcon::GraphicsDisplayIcon(QString path)
{
    icon = new QImage(QImage(path).scaled(32, 32));
}

GraphicsDisplayIcon::GraphicsDisplayIcon(QImage img)
{
    icon = new QImage(img);
}

QRectF GraphicsDisplayIcon::boundingRect() const
{
    return QRectF(0, 0, icon->width(), icon->height());
}

void GraphicsDisplayIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    painter->drawImage(icon->rect(), *icon);
}

QSize GraphicsDisplayIcon::GetSize()
{
    return icon->size();
}

void GraphicsDisplayIcon::UpdateImg(QImage img)
{
    delete icon;
    icon = new QImage();
    update();
    *icon = img;
    update();
}
