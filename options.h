#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include"widget.h"
#include<QTcpSocket>
namespace Ui {
class Options;
}

class Options : public QWidget
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);
    void Renji();
    ~Options();
    Widget *w;
    QPainter *painter;
    QTcpSocket *client;
    Ui::Options *ui;
public slots:
    void  ErrorPrint();
private:

};

#endif // OPTIONS_H
