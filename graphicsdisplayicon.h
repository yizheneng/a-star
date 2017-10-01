#ifndef GRAPHICSDISPLAYICON_H
#define GRAPHICSDISPLAYICON_H
#include <QGraphicsItem>
#include <QImage>
#include <QPainter>
#include <QObject>

class GraphicsDisplayIcon : public QObject , public QGraphicsItem
{
    Q_OBJECT

    Q_INTERFACES(QGraphicsItem)

public:
    GraphicsDisplayIcon(QString path);
    GraphicsDisplayIcon(QImage img);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;
    QSize GetSize();
    void UpdateImg(QImage img);

private:
    QImage* icon;
};

#endif // GRAPHICSDISPLAYICON_H
