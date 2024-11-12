#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPainter>
#include<QHash>
#include<QMouseEvent>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlError>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlRecord>
#include<QDebug>
#include<QLabel>
#include<QVector>
#include<QTcpServer>
#include<QTcpSocket>
#include"winwiget.h"
#include"points.h"
#include "user.h"
#include"int.h"
#include"overload.h"
//#include"options.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr,QString s1="人机",QString s2="人机");
    ~Widget();
    QPoint& MakeSure(int *b);
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void ChessPaint(QPainter& painter);
    QPoint getPoint(QPoint &p);
    void accountPlay(QMouseEvent *event);
    void  if_win();
    void  MatchinePlay();
    void matchStart();
    void matchinePlay();
    void PlayerMatchinePlay(QMouseEvent *event);
    //QSqlDatabase data;
    //QSqlQuery query;
    QVector<Points> Pointses;//存放棋子的位置
    int TwoP[19][19];
    User user1;
    User user2;
    QString winner="";
    int id_F;
    QPoint begin;//棋盘开始的坐标
    bool matchine;//是否是人机模式
    bool match=false;//用于判断是否是匹配模式
    QTcpSocket *client=nullptr;
    int i=0;//用于判断第该第几个人下棋了i如果是0就代表是人机
    int *foot;//棋盘的格子步长
    const int num=19;//棋盘的行数和列数
    int state;//判断绘画白棋还是黑棋0：黑棋，1：白棋
    double Ch_M=2.5;
    bool ifsame;//判断两次下棋的位置 是否有效
    QLabel *text;
    winWiget *winWidget;
    int winNum=5;
    bool yourtime;
    //Options *options;
signals:
    void errorClose();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
