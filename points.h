#ifndef POINTS_H
#define POINTS_H
#include<QPoint>

class Points:public QPoint
{
public:
    Points()=default;
    Points(QPoint p);
    Points(QPoint p,int i);
    int flag;//1表示白，0表示黑
};

#endif // POINTS_H
