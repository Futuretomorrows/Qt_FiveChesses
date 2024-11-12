#ifndef USER_H
#define USER_H
#include<QString>

class User
{
public:
    User();
    User(QString account);
    QString account;
    bool log=false;
};

#endif // USER_H
