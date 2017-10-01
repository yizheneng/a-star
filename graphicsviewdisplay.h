#ifndef GRAPHICSVIEWDISPLAY_H
#define GRAPHICSVIEWDISPLAY_H

#include <QGraphicsView>
#include <graphicsdisplayicon.h>
#include <QGraphicsSceneEvent>
#include <astar.h>
#include "pathitem.h"

#define START_ICON_PATH ":/icon/img/start.png"
#define END_ICON_PATH   ":/icon/img/end.png"

#define GRID_X_SIZE 10
#define GRID_Y_SIZE 10

class GraphicsViewDisplay : public QGraphicsScene
{
Q_OBJECT

public:
    GraphicsViewDisplay();
    void SetStartIconPosition(QPointF pos);
    void SetEndIconPosition(QPointF pos);
    void RunPlan();
    void ClearPath();

    int flag;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    bool IsTheGridCanPass(QImage &map, int gridMapX, int gridMapY);
    Point GridPointToRealPoint(Point& gridPoint);

signals:
    void SignalForClearButtonState(void);

public slots:
    void SlotOfUpdateMap(QImage img);

private:
    GraphicsDisplayIcon *startIcon;
    GraphicsDisplayIcon *endIcon;
    GraphicsDisplayIcon *mapImg;
    PathItem *pathImg;

    QPointF startPoint;
    QPointF endPoint;

    QImage map;

    Astar astar;
};

#endif // GRAPHICSVIEWDISPLAY_H
