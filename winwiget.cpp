#include "winwiget.h"
#include "ui_winwiget.h"

winWiget::winWiget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::winWiget)
{
    ui->setupUi(this);
}

winWiget::~winWiget()
{
    delete ui;
}
