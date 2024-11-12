#ifndef OVERLOAD_H
#define OVERLOAD_H
#include<QDataStream>
#include"IntData.h"

QDataStream& operator<<(QDataStream& out, account &p);
QDataStream& operator>>(QDataStream& in, account &p);
QDataStream& operator<<(QDataStream& out, const ifHave &p);
QDataStream& operator>>(QDataStream& in, ifHave &p);
QDataStream& operator>>(QDataStream& in, pointData &p);
QDataStream& operator<<(QDataStream& out, pointData &p);
#endif // OVERLOAD_H
