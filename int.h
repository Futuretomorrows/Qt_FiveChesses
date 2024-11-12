#ifndef INT_H
#define INT_H
#include<QString>

class Int
{
public:
    Int(int a=0);
    QString toString();
    void operator=(int a);
    Int& operator+(int a);
    operator int();
    int value;
};

#endif // INT_H
