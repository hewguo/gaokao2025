/********************************************************************************
** Form generated from reading UI file 'frmfilteroption.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMFILTEROPTION_H
#define UI_FRMFILTEROPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FrmFilterOption
{
public:
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QTreeView *treeView;

    void setupUi(QWidget *FrmFilterOption)
    {
        if (FrmFilterOption->objectName().isEmpty())
            FrmFilterOption->setObjectName("FrmFilterOption");
        FrmFilterOption->resize(159, 250);
        btnOK = new QPushButton(FrmFilterOption);
        btnOK->setObjectName("btnOK");
        btnOK->setGeometry(QRect(20, 0, 61, 32));
        btnCancel = new QPushButton(FrmFilterOption);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setGeometry(QRect(80, 0, 61, 32));
        treeView = new QTreeView(FrmFilterOption);
        treeView->setObjectName("treeView");
        treeView->setGeometry(QRect(10, 30, 141, 211));

        retranslateUi(FrmFilterOption);

        QMetaObject::connectSlotsByName(FrmFilterOption);
    } // setupUi

    void retranslateUi(QWidget *FrmFilterOption)
    {
        FrmFilterOption->setWindowTitle(QCoreApplication::translate("FrmFilterOption", "Form", nullptr));
        btnOK->setText(QCoreApplication::translate("FrmFilterOption", "\347\241\256\345\256\232", nullptr));
        btnCancel->setText(QCoreApplication::translate("FrmFilterOption", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FrmFilterOption: public Ui_FrmFilterOption {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMFILTEROPTION_H
