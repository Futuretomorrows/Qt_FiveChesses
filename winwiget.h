#ifndef WINWIGET_H
#define WINWIGET_H

#include <QWidget>

namespace Ui {
class winWiget;
}

class winWiget : public QWidget
{
    Q_OBJECT

public:
    explicit winWiget(QWidget *parent = nullptr);
    ~winWiget();
     Ui::winWiget *ui;
private:

};

#endif // WINWIGET_H
