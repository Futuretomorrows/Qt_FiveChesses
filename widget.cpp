 #include "widget.h"
#include "ui_widget.h"
#include "ui_winwiget.h"

#include <QDateTime>
#include<QByteArray>
#include<QRandomGenerator>

Widget::Widget(QWidget *parent,QString s1,QString s2)
    : QWidget(parent),user1(s1),user2(s2),state(0)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    for(int i=0;i<19;i++){
        for(int k=0;k<19;k++){
            this->TwoP[i][k]=3;
        }
    }
    this->text=new QLabel(this);
}
void Widget:: paintEvent(QPaintEvent* event){
    QPainter painter(this);
    QPen pen(Qt::PenStyle::SolidLine);
    painter.setPen(pen);
    Int wid=1;
    Int hei=1;
    this->foot=NULL;
    foot=new int(0);
    this-> begin=MakeSure(foot);
    for(int i=0;i<num;i++){
        painter.drawLine(begin+QPoint(i*(*foot),0),begin+QPoint(i*(*foot),(num-1)*(*foot)));
        painter.drawText(begin+QPoint(i*(*foot)-5,0-(*foot)/4),wid.toString());
        wid=wid+1;
        painter.drawLine(begin+QPoint(0,i*(*foot)),begin+QPoint((num-1)*(*foot),i*(*foot)));
        painter.drawText(begin+QPoint(0-(*foot)/1.5,i*(*foot)),hei.toString());
        hei=hei+1;
    }
    this->text->setGeometry((*foot)*20,(*foot)*5,250,250);
    this->ChessPaint(painter);
}
void Widget::if_win(){
    //判断是否胜利每次绘画完棋子之后判断
    if(this->Pointses.size()!=0)
    {
        Points point=this->Pointses.back();
        int x_top=point.x()+4;
        int y_top=point.y()+4;
        int x_low=point.x()-4;
        int y_low=point.y()-4;
        if(x_top>19)x_top=19;
        if(y_top>19)y_top=19;
        if(x_low<=0)x_low=1;
        if(y_low<=0)y_low=1;
        int judge1=0;
        int judge0=0;
        //检查列
//        qDebug()<<this->TwoP[point.y()-1][point.x()-1];
//        qDebug()<<point.y()-1<<" "<<point.x()-1;
//        qDebug()<<x_top<<" "<<x_low<<" "<<y_top<<" "<<y_low;
        for(int p=y_low-1;p<this->num&&p<y_top;p++){
            if(this->TwoP[p][point.x()-1]==1){
                judge0=0;
                judge1++;
                if(judge1==winNum){
                    this->winWidget=new winWiget;
                    this->winWidget->ui->Text->setText("白棋Win");
                    this->close();
                    this->winWidget->show();
                    return;
                }
            }
            if(this->TwoP[p][point.x()-1]==0){
                judge1=0;
                judge0++;
                if(judge0==winNum){
                    this->winWidget=new winWiget;
                    this->winWidget->ui->Text->setText("黑棋Win");
                    this->close();
                    this->winWidget->show();
                    return;
                }
            }
        }
        judge1=0;
        judge0=0;
        //检查行
        for(int p=x_low-1;p<this->num&&p<x_top;p++){
            if(this->TwoP[point.y()-1][p]==1){
                judge0=0;
                judge1++;
                qDebug()<<judge1;
                if(judge1==winNum){
                    this->winWidget=new winWiget;
                    this->winWidget->ui->Text->setText("白棋Win");
                    this->close();
                    this->winWidget->show();
                    return;
                }
            }
            if(this->TwoP[point.y()-1][p]==0){
                judge1=0;
                judge0++;
                if(judge0==winNum){
                    this->winWidget=new winWiget;
                    this->winWidget->ui->Text->setText("黑棋Win");
                    this->close();
                    this->winWidget->show();
                     return;
                }
            }
        }
        //左上到右下斜着检查
        judge1=0;
        judge0=0;
        for(int p=y_low-1,k=x_low-1;(p<this->num&&p<y_top)&&(k<this->num&&k<x_top);p++,k++){
            if(this->TwoP[p][k]==1){
                judge0=0;
                judge1++;
                if(judge1==winNum){
                    this->winWidget=new winWiget;
                    this->winWidget->ui->Text->setText("白棋Win");
                    this->close();
                    this->winWidget->show();
                    return;
                }
            }
            if(this->TwoP[p][k]==0){
                judge1=0;
                judge0++;
                if(judge0==winNum){
                    this->winWidget=new winWiget;
                    this->winWidget->ui->Text->setText("黑棋Win");
                    this->close();
                    this->winWidget->show();
                     return;
                }
            }
        }
        //左下到右上斜着检查
        judge1=0;
        judge0=0;
        qDebug()<<x_top<<" "<<x_low<<" "<<y_top<<" "<<y_low;
        for(int p=y_top-1,k=x_low-1;(p>=0&&p>y_low-2)&&(k<this->num&&k<x_top);p--,k++){

            if(this->TwoP[p][k]==1){
                judge0=0;
                judge1++;
                if(judge1==winNum){
                    this->winWidget=new winWiget;
                    this->winWidget->ui->Text->setText("白棋Win");
                    this->close();
                    this->winWidget->show();
                    return;
                }
            }
            if(this->TwoP[p][k]==0){
                judge1=0;
                judge0++;
                if(judge0==winNum){
                    this->winWidget=new winWiget;
                    this->winWidget->ui->Text->setText("黑棋Win");
                    this->close();
                    this->winWidget->show();
                     return;
                }
            }
        }

     }
    //赢了之后自动跳转到胜方结算画面

}
QPoint& Widget::MakeSure(int *b){
    int width = this->width();
    int height =this->height();
    *b=height/num;
    QPoint *point=new QPoint(width*1/(num*30/19),height*1/(num*30/19));
    return *point;
}
void Widget::mousePressEvent(QMouseEvent *event){
   //人机模式
   if(matchine){
      // qDebug()<<matchine;
       PlayerMatchinePlay(event);//人机模式下的人
       if_win();
       if(!ifsame){
           MatchinePlay();
           if_win();
       }
   }
   if(this->match){
       if(yourtime)accountPlay(event);
       else return;
   }
}
void Widget::PlayerMatchinePlay(QMouseEvent *event){
    if(event->x()>this->begin.x()+*foot*(num-0.6)||event->y()>this->begin.y()+*foot*(num-0.6))
    {
        return ;
    }
    if(event->x()<this->begin.x()-*foot||event->y()<this->begin.y()-*foot)
    {
        return ;
    }
    QPoint p(event->x(),event->y());
    QPoint Rp=getPoint(p);//得到棋盘坐标
    int x=(Rp.x()-this->begin.x())/(*(this->foot));
    int y=(Rp.y()-this->begin.y())/(*(this->foot));
    QPoint po(x+1,y+1);
    //如果这个位置已经有旗子了那就不用在执行了
    for(auto t:this->Pointses){
        if(t==po){
            this->ifsame=true;
            return;
        }
    }
    this->ifsame=false;
    this->TwoP[y][x]=1;
    this->Pointses.push_back(Points(po,1));
    //qDebug()<<this->Pointses;
    update();
}
void Widget::MatchinePlay(){
    Points p=this->Pointses.back();
    A:int x = QRandomGenerator::global()->bounded(1, 19);
    int y = QRandomGenerator::global()->bounded(1, 19);
    QPoint po(x,y);
    for(auto t:this->Pointses){
        if(t==po)goto A;
    }
    this->Pointses.push_back(Points(po,0));
    qDebug()<<x;
    qDebug()<<y;
    this->TwoP[y-1][x-1]=0;
    update();
}
void Widget::accountPlay(QMouseEvent *event){
    if(event->x()>this->begin.x()+*foot*(num-0.6)||event->y()>this->begin.y()+*foot*(num-0.6))
    {
        return ;
    }
    if(event->x()<this->begin.x()-*foot||event->y()<this->begin.y()-*foot)
    {
        return ;
    }
    QPoint p(event->x(),event->y());
    QPoint Rp=getPoint(p);//得到棋盘坐标
    int x=(Rp.x()-this->begin.x())/(*(this->foot));
    int y=(Rp.y()-this->begin.y())/(*(this->foot));
    QPoint po(x+1,y+1);
    //如果这个位置已经有旗子了那就不用在执行了
    for(auto t:this->Pointses){
        if(t==po)return;
    }
    this->Pointses.push_back(Points(po,state));
    if(this->match){
        //客户端是先发再读
        QByteArray buff;
        int hx=this->Pointses.back().x();
        int hy=this->Pointses.back().y();
        pointData temp;
        temp.x=hx;
        temp.y=hy;
        temp.color=this->state;
        temp.type=7;
        QDataStream out(&buff,QIODevice::WriteOnly);
        out>>temp;
        this->client->write(buff);
        this->client->flush();
        yourtime=false;
    }
}
QPoint Widget::getPoint(QPoint &p){
    int X;
    int Y;
    int a=((p.x()-this->begin.x())/(*(this->foot)));
    int b=((p.y()-this->begin.y())/(*(this->foot)));
    if(p.x()-a*(*(this->foot))-begin.x()<begin.x()+(a+1)*(*(this->foot))-p.x())
    {
        X=a;
    }
    else {
        X=a+1;
    }
    if(p.y()-b*(*(this->foot))-begin.y()<begin.y()+(b+1)*(*(this->foot))-p.y())
        Y=b;
    else Y=b+1;
    return QPoint(begin+QPoint(X*(*(this->foot)),Y*(*(this->foot))));

}
void Widget::ChessPaint(QPainter& painter){
    //qDebug()<<this->Pointses;
    for(auto point:Pointses){
        //qDebug()<<point.flag;
        if(point.flag==1){
            QBrush *b=new QBrush(Qt::white);
            painter.setBrush(*b);
        }
        if(point.flag==0){
             QBrush *b=new QBrush(Qt::black);
            painter.setBrush(*b);
        }
        QPoint base=this->begin+QPoint((point.x()-1)*(*foot),(point.y()-1)*(*foot));
        QRectF chessSize(QPointF(base.x()-(*(this->foot))/this->Ch_M,base.y()-(*(this->foot))/this->Ch_M),QPointF(base.x()+(*(this->foot))/this->Ch_M,base.y()+(*(this->foot))/this->Ch_M));
        painter.drawEllipse(chessSize);
    }
}

Widget::~Widget()
{
    delete ui;
}

