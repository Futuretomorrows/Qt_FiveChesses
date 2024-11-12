#include "int.h"

Int::Int(int a):value(a)
{

}
void Int::operator=(int a){
    this->value=a;
}
Int& Int::operator+(int a){
    this->value+=a;
    return *this;
}
Int::operator int(){
    return this->value;
}
QString Int::toString(){
    QString str="";
    int tmp=this->value;
    while(tmp>=10){
        int t=tmp%10;
        char l='0'+t;
        str=l+str;
        tmp/=10;
    }
    char l=(char)'0'+tmp;
    str=l+str;
    return str;
}
