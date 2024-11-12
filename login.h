#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlError>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlRecord>
#include<QPainter>
#include<QTcpSocket>
#include<QTcpServer>
#include<QByteArray>

#include"widget.h"
#include"user.h"
#include"eroll.h"
#include"options.h"

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    void select_user();
    void Zhuce_All();
    void Zhuce();
    bool IntStart();
    void select();
    void matchinePlay();
    void Match();
//    Widget *wid;
    Eroll* w;//注册页面
    Options *w_option;//选择界面
    QTcpSocket *client;
    QPainter painter;
    User User;
    bool Intnert;
    ~login();


private:
    Ui::login *ui;
};


#endif // LOGIN_H
