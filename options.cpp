#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    //链接options界面的匹配模式，与Widget界面
     this->w=new Widget;
    //人机对战
    //connect(ui->PlayerToInet,&QPushButton::clicked,this,&Options::Renji);
    //联机
//    connect(ui->matching,&QPushButton::clicked,this->w,[=](){
//        this->close();
//        this->w->matchStart();});
   // connect(this->w,&Widget::errorClose,this,&Options::ErrorPrint);
    //匹配



}
void Options::ErrorPrint(){
    this->painter=new QPainter;
    painter->drawText(QPoint(this->width()/10,this->height()/10),"服务器连接失败，或服务器未打开");
}
void Options::Renji(){
    this->w->matchine=true;
    this->w->user2.account="人机";
    this->w->winner="";
    this->close();
    this->w->showMaximized();
}
Options::~Options()
{
    delete ui;
}
