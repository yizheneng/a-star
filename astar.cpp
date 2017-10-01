#include "astar.h"

Astar::Astar(): mapSizeX(0), mapSizeY(0), startFlag(false)
{
}

Astar::~Astar()
{
    DeleteMap();
}

void Astar::SetMapSize(int x, int y)
{
    DeleteMap();

    map = new astar_struct[x * y];

    mapSizeX = x;
    mapSizeY = y;

    memset(map, 0, x * y * sizeof(astar_struct));
}

void Astar::DeleteMap()
{
    if((mapSizeX * mapSizeY) > 0)
    {delete[] map;}
}

void Astar::ClearMap()
{
    memset(map, 0, mapSizeX * mapSizeY * sizeof(astar_struct));
}

void Astar::SetMapPoint(int x, int y, bool isEnable)
{
    if((x < mapSizeX) && (y < mapSizeY))
        Map(x,y)->isEnable = isEnable;
}

void Astar::SetStarPoint(int x, int y)
{
    memset(&startPoint, 0, sizeof(astar_struct));

    startPoint.point.x = x;
    startPoint.point.y = y;
}

void Astar::SetEndPoint(int x, int y)
{
    memset(&endPoint, 0, sizeof(astar_struct));

    endPoint.point.x = x;
    endPoint.point.y = y;
}

bool Astar::IsThePointInThisGroup(vector<astar_struct> *pointGroup, Point point)
{
    vector<astar_struct>::iterator it = pointGroup->begin();

    for(; it != pointGroup->end(); it++)
    {
        if(memcmp(&((*it).point), &point, sizeof(Point)) == 0)
        {
            return true;
        }
    }
    return false;
}

char Astar::RunAstar()
{
    while(1)
    {
        if(startFlag == false)
        {
            openPoint.clear();
            closePoint.clear();
            path.clear();

            InsertOpenpoint(&startPoint);

            startFlag = true;
        }

        if(startFlag == true)
        {
            astar_struct temp;

            if(openPoint.size() == 0)
            {
                return -1;
            }else
            {
                memcpy(&temp, &openPoint.at(0), sizeof(astar_struct));

                openPoint.erase(openPoint.begin());

                closePoint.push_back(temp);

                if(RunAstarOnce(temp.point) == false)
                {
                    startFlag = false;
                    return 1;
                }
            }
        }
    }
}

bool Astar::RunAstarOnce(Point point)
{
    Point tempPoint;
    astar_struct* currentItem = Map(point.x,point.y);
    astar_struct* tempItem;
    int gval,hval;

    for(int i = 0; i < 8; i++)
    {
        switch (i) {
        case 0://left up point
            tempPoint.x = point.x - 1;
            tempPoint.y = point.y - 1;

            if((Map(tempPoint.x,tempPoint.y - 1)->isEnable == false)
                    && (Map(tempPoint.x -1 , tempPoint.y)->isEnable == false))
            {
                continue;
            }
            gval = DIAGONAL_DISTANCE + currentItem->gVal;
            break;
        case 1://left under point
            tempPoint.x = point.x - 1;
            tempPoint.y = point.y + 1;

            if((Map(point.x - 1,point.y)->isEnable == false)
                    && (Map(point.x,point.y + 1)->isEnable == false))
            {
                continue;
            }
            gval = DIAGONAL_DISTANCE + currentItem->gVal;
            break;
        case 2://right up point
            tempPoint.x = point.x + 1;
            tempPoint.y = point.y - 1;

            if((Map(point.x,point.y - 1)->isEnable == false)
                    && (Map(point.x + 1,point.y)->isEnable == false))
            {
                continue;
            }
            gval = DIAGONAL_DISTANCE + currentItem->gVal;
            break;
        case 3://right under point
            tempPoint.x = point.x + 1;
            tempPoint.y = point.y + 1;

            if((Map(point.x + 1,point.y)->isEnable == false)
                    && (Map(point.x,point.y + 1)->isEnable == false))
            {
                continue;
            }
            gval = DIAGONAL_DISTANCE + currentItem->gVal;
            break;
        case 4://upside point
            tempPoint.x = point.x;
            tempPoint.y = point.y - 1;
            gval = LINE_DISTANCE + currentItem->gVal;
            break;
        case 5://underside point
            tempPoint.x = point.x;
            tempPoint.y = point.y + 1;
            gval = LINE_DISTANCE + currentItem->gVal;
            break;
        case 6://leftside point
            tempPoint.x = point.x - 1;
            tempPoint.y = point.y;
            gval = LINE_DISTANCE + currentItem->gVal;
            break;
        case 7://rightside point
            tempPoint.x = point.x + 1;
            tempPoint.y = point.y;
            gval = LINE_DISTANCE + currentItem->gVal;
            break;
        default:
            break;
        }

        if((tempPoint.x >= 0) && (tempPoint.y >= 0) && (tempPoint.x < mapSizeX) && (tempPoint.y < mapSizeY))
        {
            if((!IsThePointInThisGroup(&closePoint, tempPoint)) && ((tempItem = Map(tempPoint.x,tempPoint.y))->isEnable == true))
            {
                if(memcmp(&tempPoint, &endPoint, sizeof(Point)) == 0)
                {
                    tempItem->father_point.x = point.x;
                    tempItem->father_point.y = point.y;

                    DrawPath();
                    return false;
                }
                if(!IsThePointInThisGroup(&openPoint, tempPoint))//isn't in openPoint
                {
                    tempItem->gVal = gval;

                    hval = abs(endPoint.point.x-tempPoint.x) * 10 + abs(endPoint.point.y-tempPoint.y) * 10;
                    tempItem->hVal = (hval);
                    tempItem->fVal = hval + gval;
                    tempItem->father_point.x = point.x;
                    tempItem->father_point.y = point.y;
                    tempItem->point.x = tempPoint.x;
                    tempItem->point.y = tempPoint.y;

                    InsertOpenpoint(tempItem);
                }else   //in open point
                {
                    if(gval < tempItem->gVal)
                    {
                        tempItem->gVal = gval;

                        hval = abs(endPoint.point.x-tempPoint.x) * 10 + abs(endPoint.point.y-tempPoint.y) * 10;

                        tempItem->hVal = hval;
                        tempItem->fVal = hval + gval;
                        tempItem->father_point.x = point.x;
                        tempItem->father_point.y = point.y;
                        tempItem->point.x = tempPoint.x;
                        tempItem->point.y = tempPoint.y;

                        InsertOpenpoint(tempItem);
                    }
                }
            }
        }
    }
    return true;
}

void Astar::InsertOpenpoint(astar_struct *point)
{
    if(openPoint.size() == 0)
    {
        openPoint.push_back(*point);
    }else
    {

        vector<astar_struct>::iterator itor = openPoint.begin();

        for(; itor != openPoint.end(); itor++)
        {
            if(point->fVal < (*itor).fVal)
            {
                break;
            }
        }

        openPoint.insert(itor, *point);
    }
}

void Astar::DrawPath()
{
    Point tempPoint;
    astar_struct *tempItem;

    path.clear();

    tempItem = &endPoint;

    tempPoint.x = endPoint.point.x;
    tempPoint.y = endPoint.point.y;

    while(1)
    {
        if((tempPoint.x == startPoint.point.x) && (tempPoint.y == startPoint.point.y))
            break;

        tempItem = Map(tempPoint.x,tempPoint.y);

        if((tempItem->father_point.x ==  tempPoint.x)
                && (tempItem->father_point.y ==  tempPoint.y))
        {
            return;
        }

        tempPoint.x = tempItem->father_point.x;
        tempPoint.y = tempItem->father_point.y;

        path.push_back(tempPoint);
    }

//    vector<Point>::iterator itr = path.begin();

//    for(; (itr + 2) != path.end();)
//    {
//        if((((*(itr + 1)).x - (*(itr)).x) == ((*(itr + 2)).x - (*(itr + 1)).x))
//                && (((*(itr + 1)).y - (*(itr)).y) == ((*(itr + 2)).y - (*(itr + 1)).y)))
//        {
//            path.erase(itr);
//            path.erase(itr + 1);
//        }else
//        {
//            itr ++;
//        }
//    }
}

astar_struct* Astar::Map(int x, int y)
{
    return map + (y*mapSizeX + x);
}
