#include "login.h"
#include "ui_login.h"
#include"ui_options.h"
#include<QDebug>
#include"widget.h"
#include"overload.h"
login::login(QWidget *parent) :
    QWidget(parent),//,Intnert(false),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //qDebug()<<"kjsdifj";
    if(!IntStart()){
        this->ui->Text->setText("无法连接网络");
    }
    else{
         connect(this->client,&QTcpSocket::readyRead,this,&login::select);
    }
    //人机按键
    connect(ui->machine,&QPushButton::clicked,this,&login::matchinePlay);
    //登录按键
    connect(ui->loginButton,&QPushButton::clicked,this,&login::select_user);
    //注册按键
    connect(ui->enroll,&QPushButton::clicked,this,&login::Zhuce_All);
    //匹配在第169行
}
void login::matchinePlay(){
    this->w_option=new Options;
    this->w_option->w=new Widget;
    this->w_option->w->showMaximized();
    this->w_option->w->matchine=true;
    this->close();
}
void login::select_user(){
    if(!this->Intnert){
        this->ui->Text->setText("无网络，无法登陆");
        return ;
    }
    //qDebug()<<"kmkjlj";
    QString account=this->ui->acount->text();
    QString password=this->ui->password->text();
    QByteArray array;
    QDataStream out(&array,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);
    struct account IntAccount(account,password);
    IntAccount.type=3;
   // qDebug()<<array.size();
    out<<IntAccount;
//    int messageSize = array.size();
//    qDebug()<<messageSize;
//    out.device()->seek(0);
//    out << (qint32)(messageSize);  // 写入总消息长度（包括长度字段本身）
//    qDebug()<<messageSize+sizeof(qint32)<<"  "<<out.device()->size()<<array.size() ;
    client->write(array);
    client->flush();

    qDebug()<<"lmkf";

}
void login::Zhuce_All(){
    if(!this->Intnert){
        this->ui->Text->setText("无网络，无法注册");
        return ;
    }
    this->w=new Eroll;//在这里申请空间主要是考虑到大部分情况的话其实并不需要注册页面的打开
    w->setFixedSize(900,715);
    w->show();
    w->ui->label->setText("账号密码请均不要超过21位");
    connect(this->w->ui->log,&QPushButton::clicked,this,&login::Zhuce);
    connect(this->w->ui->returns,&QPushButton::clicked,w,&Eroll::close);
}
void login::Zhuce(){
    QString account=this->w->ui->lineAcount->text();
    QString password=this->w->ui->linePassword->text();
    QString password2=this->w->ui->linePassAgain->text();
    if(account.size()>21){
        this->w->ui->label->clear();
        this->w->ui->label->setText("您的账户名超过了21位");
    }
   else if(password.size()>21){
        this->w->ui->label->clear();
        this->w->ui->label->setText("您输入的密码超过了21位");
    }
   else if(password!=password2){
        this->w->ui->label->clear();
        this->w->ui->label->setText("两次密码不一致");
    }
   else {
          if(!this->Intnert){
              this->w->ui->Text->setText("无法连接服务器，无法注册");
          }
          else{
              QByteArray array;
              QDataStream out(&array,QIODevice::WriteOnly);
              out.setVersion(QDataStream::Qt_5_14);
              struct account IntAccount(account,password);
              out<<IntAccount;
              client->write(array);
              client->flush();
          }
    }
}
bool login::IntStart(){
    qDebug()<<" IntStart2 is good";
    this->client=new QTcpSocket(this);
    client->connectToHost("10.67.75.192",9091);
    if(!client->waitForConnected(50000)){
        qDebug()<<client->errorString();
        this->Intnert=false;
        return false;
    }
    else {
        connect(client,&QTcpSocket::readyRead,this,&login::select);
        qDebug()<<" IntStart is good";
        this->Intnert=true;
        return true;
    }
}
void login::select(){
    qDebug()<<" select is good";
    qint8 type=0;
    qint32 b=88;
    QDataStream in(this->client);
    in.setVersion(QDataStream::Qt_5_14);
//    while(this->client->bytesAvailable()){
//        if(client->bytesAvailable()>=(int)sizeof(qint32))
//            break;
//    }
//    in>>b;
//    while(this->client->bytesAvailable()){
//        if(client->bytesAvailable()>=b)
//            break;
//    }
    in>>type;
    qDebug()<<" type "<<type;
    switch (type) {
    case 2:
    {
        //qDebug()<<"22";//注册但是已经有人了
        ifHave haves;
        in>>haves.have;
        if(haves.have){
            this->w->ui->Text->setText("该用户名已经有人喽");
        }
        else{
            this->w->ui->Text->setText("创建成功喽，请返回登录");
        }
        break;
    }
    case 3://登录使用结构体
    {
        ifHave haves;
        in>>haves.have;
        if(haves.have){
            this->w_option=new Options;
            //选项匹配按键
            connect(this->w_option->ui->matching,&QPushButton::clicked,this,&login::Match);
            this->close();
            this->w_option->show();
        }
        else{
            this->w->ui->Text->setText("账号或密码错误");
        }
        break;
    }
    case 5://服务器返回确定棋子颜色
    {
        qDebug()<<"show is good";
        this->w_option->ui->Text->setText("you are 白棋,你先下");
        int color=0;
        in<<color;
        this->w_option->w->state=color;
        if(color==1)
        {this->w_option->w->text->setText("you are 白棋,你先下");
        this->w_option->ui->Text->setText("you are 白棋,你先下");
        this->w_option->w->yourtime=true;}
        if(color==0)
        {this->w_option->w->text->setText("你是黑棋，你后下");
        this->w_option->ui->Text->setText("you are heiqi,你先下");
        this->w_option->w->yourtime=false;}
        this->w_option->w->client=this->client;
        qDebug()<<"show is good";
       // this->w_option->hide();
        this->w_option->w->show();
        break;
    }
    case 6:{
           this->w_option->ui->Text->setText("正在匹配中哦，别着急哦");
        break;
    }
    case 7:{
        pointData p;
        in>>p;
        this->w_option->w->yourtime=true;
        Points point;
        point.setX(p.x);
        point.setY(p.y);
        point.flag=p.color;
        this->w_option->w->Pointses.push_back(point);
        this->w_option->w->update();
    }
}}
void login::Match(){
    QByteArray array;
    QDataStream out(&array,QIODevice::WriteOnly);
    qint8 a=4;
    out<<a;
    this->client->write(array);
    this->client->flush();
    this->w_option->w->match=true;
}
login::~login()
{
    delete ui;
}
