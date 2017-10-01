#include "graphicsviewdisplay.h"
#include <QMessageBox>
#include <QDebug>

GraphicsViewDisplay::GraphicsViewDisplay() : flag(0)
{
   startIcon = new GraphicsDisplayIcon(START_ICON_PATH);
   endIcon = new GraphicsDisplayIcon(END_ICON_PATH);
   mapImg = new GraphicsDisplayIcon("");
   pathImg = new PathItem();

   this->addItem(mapImg);
   this->addItem(pathImg);
   this->addItem(startIcon);
   this->addItem(endIcon);
}

void GraphicsViewDisplay::SetStartIconPosition(QPointF pos)
{
    startIcon->setPos(pos);
}

void GraphicsViewDisplay::SetEndIconPosition(QPointF pos)
{
    endIcon->setPos(pos);
}

void GraphicsViewDisplay::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF temp;
    if(event->button() == Qt::LeftButton)
    {
        switch (flag) {
        case 1:
            temp.setX(event->buttonDownScenePos(Qt::LeftButton).x() - startIcon->GetSize().width() / 2);
            temp.setY(event->buttonDownScenePos(Qt::LeftButton).y() - startIcon->GetSize().height());

            SetStartIconPosition(temp);

            startPoint = event->buttonDownScenePos(Qt::LeftButton);
            break;
        case 2:
            temp.setX(event->buttonDownScenePos(Qt::LeftButton).x() - endIcon->GetSize().width() / 2);
            temp.setY(event->buttonDownScenePos(Qt::LeftButton).y() - endIcon->GetSize().height());

            SetEndIconPosition(temp);

            endPoint = event->buttonDownScenePos(Qt::LeftButton);
            break;
        default:
            break;
        }
        emit SignalForClearButtonState();
    }
}

void GraphicsViewDisplay::SlotOfUpdateMap(QImage img)
{
    map = img;
    mapImg->UpdateImg(img);

    pathImg->SetSize(img.width(), img.height());
}

void GraphicsViewDisplay::RunPlan()
{
    int gridMapSizeX = 0;
    int gridMapSizeY = 0;

    if((startPoint.x() < 0) || (startPoint.y() < 0) || (endPoint.x() < 0) || (endPoint.y() < 0))
    {
        QMessageBox::warning(0, tr("error!"), "startPoint or endPoint error!!!",QMessageBox::Ok);
        return;
    }

    /*********原始地图转换为格子地图***************/
    gridMapSizeX = map.width() / GRID_X_SIZE;
    gridMapSizeY = map.height() / GRID_Y_SIZE;

    if((map.width() % GRID_X_SIZE) > 0)
    {
        gridMapSizeX ++;
    }

    if((map.height() / GRID_Y_SIZE) > 0)
    {
        gridMapSizeY ++;
    }

    astar.SetMapSize(gridMapSizeX, gridMapSizeY);

    astar.ClearMap();

    for(int j = 0; j < gridMapSizeY; j++)
    {
        for(int i = 0; i < gridMapSizeX; i++)
        {
            astar.SetMapPoint(i,j,IsTheGridCanPass(map, i, j));
        }
    }
    /***************End*************************/

//    astar.SetMapSize(map.width(), map.height());

//    astar.ClearMap();

//    for(int j = 0; j < map.height(); j++)
//    {
//        for(int i = 0; i < map.width(); i++)
//        {
//            if((map.pixel(i,j) & 0xff) < 100)
//            {
//                astar.SetMapPoint(i,j,false);
//            }else
//            {
//                astar.SetMapPoint(i,j,true);
//            }
//        }
//    }

    astar.SetStarPoint(startPoint.x() / GRID_X_SIZE, startPoint.y() / GRID_Y_SIZE);
    astar.SetEndPoint(endPoint.x() / GRID_X_SIZE, endPoint.y() / GRID_Y_SIZE);

    if(astar.RunAstar() > 0)
    {
        vector<Point> path;
        vector<Point>* gridPath = astar.GetPath();

        /********转换栅格地图的路径到真实地图*************/

        for(int i = 0; i < gridPath->size(); i ++)
        {
            path.push_back(GridPointToRealPoint((gridPath->at(i))));
        }

        /*********End*********/

        pathImg->SetPath(&path);
        QMessageBox::warning(0, tr("warnning!"), "find the end point!!!",QMessageBox::Ok);
    }else
    {
        QMessageBox::warning(0, tr("error!"), "can't find the end point!!!",QMessageBox::Ok);
    }
}

void GraphicsViewDisplay::ClearPath()
{
    vector<Point> temp;

    pathImg->SetPath(&temp);
}

bool GraphicsViewDisplay::IsTheGridCanPass(QImage &map, int gridMapX, int gridMapY)
{
    gridMapX *= GRID_X_SIZE;
    gridMapY *= GRID_Y_SIZE;

    for(int i = 0; i < GRID_X_SIZE * GRID_Y_SIZE; i++)
    {
        if(((gridMapX + i % GRID_X_SIZE) >= map.width()) || ((gridMapY + i % GRID_X_SIZE) >= map.height()))
        {
            continue;
        }

        if((map.pixel(gridMapX + i % GRID_X_SIZE,gridMapY + i % GRID_X_SIZE) & 0xff) < 100)
            return false;
    }

    return true;
}

Point GraphicsViewDisplay::GridPointToRealPoint(Point &gridPoint)
{
    Point point;

    point.x = gridPoint.x * GRID_X_SIZE + GRID_X_SIZE / 2;
    point.y = gridPoint.y * GRID_Y_SIZE + GRID_Y_SIZE / 2;

    return point;
}
