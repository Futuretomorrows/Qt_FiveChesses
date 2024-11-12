#ifndef EROLL_H
#define EROLL_H

#include <QWidget>
#include "ui_eroll.h"
namespace Ui {
class Eroll;
}

class Eroll : public QWidget
{
    Q_OBJECT

public:
    explicit Eroll(QWidget *parent = nullptr);
    ~Eroll();

    Ui::Eroll *ui;
};

#endif // EROLL_H
