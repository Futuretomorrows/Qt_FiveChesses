#ifndef INTDATA_H
#define INTDATA_H

#endif // INTDATA_H
#include<QString>
#include <QDataStream>
struct account{
    account();
    account(QString p,QString w);
    QString accounts;
    QString password;
    qint8 type=1;
};
struct ifHave{
    qint8 type=2;
    bool have=false;
};
struct pointData{
    qint8 type;
    int color;
    int x;
    int y;
};
