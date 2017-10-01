#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <string.h>
#include <stdlib.h>

#define DIAGONAL_DISTANCE   20
#define LINE_DISTANCE 10

using namespace std;

struct Point
{
    int x;
    int y;
};

struct astar_struct
{
    Point point;
    Point father_point;
    bool isEnable;
    int gVal;
    int hVal;
    int fVal;
};

class Astar
{
public:
    Astar();
    ~Astar();

    void SetMapSize(int x, int y);
    void DeleteMap();
    void SetMapPoint(int x, int y, bool isEnable);
    bool GetMapPoint(int x, int y);
    void SetStarPoint(int x, int y);
    void SetEndPoint(int x, int y);
    bool RunAstarOnce(Point point);
    void ClearMap(void);
    char RunAstar(void);
    vector<Point>* GetPath(void) {return &path;}

private:
    bool IsThePointInThisGroup(vector<astar_struct>* pointGroup, Point point);
    void InsertOpenpoint(astar_struct* point);
    void DrawPath(void);
    astar_struct* Map(int x, int y);

    vector<astar_struct> openPoint;
    vector<astar_struct> closePoint;
    vector<Point> path;

    astar_struct startPoint;
    astar_struct endPoint;
    bool startFlag;

    int mapSizeX;
    int mapSizeY;
    astar_struct* map;
};

#endif // ASTAR_H
