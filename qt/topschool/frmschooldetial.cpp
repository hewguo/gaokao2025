#include "frmschooldetial.h"
#include "ui_frmschooldetial.h"

FrmSchoolDetial::FrmSchoolDetial(QString detail,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmSchoolDetial)
{
    ui->setupUi(this);
    ui->lbSchoolDetail->setText(detail);
    //pop窗口
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    //居中显示
    if(parent){
        QRect rect=parent->geometry();
        int x=rect.x()+rect.width()/2-this->width()/2;
        int y=rect.y()+rect.height()/2-this->height()/2;
        this->move(x,y);
    }

}

FrmSchoolDetial::~FrmSchoolDetial()
{
    delete ui;
}
