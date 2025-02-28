/********************************************************************************
** Form generated from reading UI file 'frmschooldetial.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSCHOOLDETIAL_H
#define UI_FRMSCHOOLDETIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FrmSchoolDetial
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *lbSchoolDetail;

    void setupUi(QWidget *FrmSchoolDetial)
    {
        if (FrmSchoolDetial->objectName().isEmpty())
            FrmSchoolDetial->setObjectName("FrmSchoolDetial");
        FrmSchoolDetial->resize(666, 646);
        gridLayout = new QGridLayout(FrmSchoolDetial);
        gridLayout->setObjectName("gridLayout");
        scrollArea = new QScrollArea(FrmSchoolDetial);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 640, 620));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName("verticalLayout");
        lbSchoolDetail = new QLabel(scrollAreaWidgetContents);
        lbSchoolDetail->setObjectName("lbSchoolDetail");
        lbSchoolDetail->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        lbSchoolDetail->setWordWrap(true);

        verticalLayout->addWidget(lbSchoolDetail);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(FrmSchoolDetial);

        QMetaObject::connectSlotsByName(FrmSchoolDetial);
    } // setupUi

    void retranslateUi(QWidget *FrmSchoolDetial)
    {
        FrmSchoolDetial->setWindowTitle(QCoreApplication::translate("FrmSchoolDetial", "Form", nullptr));
        lbSchoolDetail->setText(QCoreApplication::translate("FrmSchoolDetial", "\345\255\246\346\240\241\347\256\200\344\273\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FrmSchoolDetial: public Ui_FrmSchoolDetial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSCHOOLDETIAL_H
