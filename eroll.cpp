#include "eroll.h"
#include "ui_eroll.h"

Eroll::Eroll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Eroll)
{
    ui->setupUi(this);
}

Eroll::~Eroll()
{
    delete ui;
}
