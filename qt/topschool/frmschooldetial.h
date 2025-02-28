#ifndef FRMSCHOOLDETIAL_H
#define FRMSCHOOLDETIAL_H

#include <QWidget>

namespace Ui {
class FrmSchoolDetial;
}

class FrmSchoolDetial : public QWidget
{
    Q_OBJECT

public:
    explicit FrmSchoolDetial(QString detail,QWidget *parent = nullptr);
    ~FrmSchoolDetial();

private:
    Ui::FrmSchoolDetial *ui;
};

#endif // FRMSCHOOLDETIAL_H
