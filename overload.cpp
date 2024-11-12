#include "overload.h"

QDataStream& operator<<(QDataStream& out, account &p){
    out<<p.type<<p.accounts<<p.password;
    return out;
}
QDataStream& operator>>(QDataStream& in, account &p){
    in>>p.type>>p.accounts>>p.password;
    return in;
}
QDataStream& operator<<(QDataStream& out, const ifHave &p){
    out<<p.type<<p.have;
    return out;
}
QDataStream& operator>>(QDataStream& in, ifHave &p){
    in>>p.type>>p.have;
    return in;
}
QDataStream& operator>>(QDataStream& in, pointData &p){
    in>>p.x>>p.y>>p.color;
    return in;
}
QDataStream& operator<<(QDataStream& out, pointData &p){
    out<<p.x<<p.y<<p.color;
    return out;
}
