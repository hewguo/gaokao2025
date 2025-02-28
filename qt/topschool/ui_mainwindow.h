/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tabcollegelist;
    QLabel *label;
    QLineEdit *leCollegeName;
    QPushButton *btnSearch;
    QLabel *label_2;
    QComboBox *cbProvince;
    QComboBox *cbCity;
    QLabel *label_3;
    QComboBox *cbType;
    QGroupBox *groupBox;
    QCheckBox *cbTagsyl;
    QCheckBox *cbTag985;
    QCheckBox *cbTag211;
    QCheckBox *cbTagqjjh;
    QComboBox *cbbxms;
    QComboBox *cbzsms;
    QTableView *tvCollegeData;
    QWidget *tabgaokao;
    QLabel *lbIcon;
    QLabel *lbCollegeName;
    QLabel *lbDangci;
    QLabel *lbAbstract;
    QLabel *label_4;
    QLabel *lbmajor;
    QTableView *tvSchoolScore;
    QTableView *tvMajorScore;
    QPushButton *btnSchoolDetail;
    QWidget *tabMajor;
    QLabel *label_5;
    QComboBox *cbYear;
    QLabel *label_6;
    QLineEdit *edtMajor;
    QPushButton *btnMajor;
    QTableView *tvMajor;
    QWidget *tabPlan;
    QTableView *tvPlan;
    QLabel *label_7;
    QComboBox *cbPlanYear;
    QLineEdit *edtPlanSchool;
    QPushButton *btnPlan;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *edtPlanMajor;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(839, 634);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 821, 501));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setTabPosition(QTabWidget::North);
        tabcollegelist = new QWidget();
        tabcollegelist->setObjectName("tabcollegelist");
        label = new QLabel(tabcollegelist);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 58, 16));
        leCollegeName = new QLineEdit(tabcollegelist);
        leCollegeName->setObjectName("leCollegeName");
        leCollegeName->setGeometry(QRect(70, 20, 181, 21));
        btnSearch = new QPushButton(tabcollegelist);
        btnSearch->setObjectName("btnSearch");
        btnSearch->setGeometry(QRect(650, 70, 100, 32));
        label_2 = new QLabel(tabcollegelist);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(270, 20, 58, 16));
        cbProvince = new QComboBox(tabcollegelist);
        cbProvince->setObjectName("cbProvince");
        cbProvince->setGeometry(QRect(310, 10, 111, 32));
        cbCity = new QComboBox(tabcollegelist);
        cbCity->setObjectName("cbCity");
        cbCity->setGeometry(QRect(430, 10, 121, 32));
        label_3 = new QLabel(tabcollegelist);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(560, 20, 58, 16));
        cbType = new QComboBox(tabcollegelist);
        cbType->setObjectName("cbType");
        cbType->setGeometry(QRect(620, 10, 141, 32));
        groupBox = new QGroupBox(tabcollegelist);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 50, 331, 61));
        cbTagsyl = new QCheckBox(groupBox);
        cbTagsyl->setObjectName("cbTagsyl");
        cbTagsyl->setGeometry(QRect(10, 30, 71, 20));
        cbTag985 = new QCheckBox(groupBox);
        cbTag985->setObjectName("cbTag985");
        cbTag985->setGeometry(QRect(100, 30, 61, 20));
        cbTag211 = new QCheckBox(groupBox);
        cbTag211->setObjectName("cbTag211");
        cbTag211->setGeometry(QRect(180, 30, 61, 20));
        cbTagqjjh = new QCheckBox(groupBox);
        cbTagqjjh->setObjectName("cbTagqjjh");
        cbTagqjjh->setGeometry(QRect(250, 30, 85, 20));
        cbbxms = new QComboBox(tabcollegelist);
        cbbxms->setObjectName("cbbxms");
        cbbxms->setGeometry(QRect(360, 70, 131, 32));
        cbzsms = new QComboBox(tabcollegelist);
        cbzsms->setObjectName("cbzsms");
        cbzsms->setGeometry(QRect(500, 70, 131, 32));
        tvCollegeData = new QTableView(tabcollegelist);
        tvCollegeData->setObjectName("tvCollegeData");
        tvCollegeData->setGeometry(QRect(10, 120, 821, 401));
        tabWidget->addTab(tabcollegelist, QString());
        tabgaokao = new QWidget();
        tabgaokao->setObjectName("tabgaokao");
        lbIcon = new QLabel(tabgaokao);
        lbIcon->setObjectName("lbIcon");
        lbIcon->setGeometry(QRect(40, 30, 120, 120));
        lbIcon->setStyleSheet(QString::fromUtf8("border: 1px solid blue;"));
        lbCollegeName = new QLabel(tabgaokao);
        lbCollegeName->setObjectName("lbCollegeName");
        lbCollegeName->setGeometry(QRect(180, 20, 631, 41));
        QFont font;
        font.setPointSize(30);
        font.setBold(true);
        font.setUnderline(true);
        lbCollegeName->setFont(font);
        lbDangci = new QLabel(tabgaokao);
        lbDangci->setObjectName("lbDangci");
        lbDangci->setGeometry(QRect(180, 130, 278, 20));
        lbDangci->setStyleSheet(QString::fromUtf8("border: 1px solid blue;"));
        lbDangci->setMidLineWidth(0);
        lbAbstract = new QLabel(tabgaokao);
        lbAbstract->setObjectName("lbAbstract");
        lbAbstract->setGeometry(QRect(180, 80, 281, 16));
        label_4 = new QLabel(tabgaokao);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 170, 81, 16));
        lbmajor = new QLabel(tabgaokao);
        lbmajor->setObjectName("lbmajor");
        lbmajor->setGeometry(QRect(430, 170, 81, 16));
        tvSchoolScore = new QTableView(tabgaokao);
        tvSchoolScore->setObjectName("tvSchoolScore");
        tvSchoolScore->setGeometry(QRect(10, 190, 391, 281));
        tvMajorScore = new QTableView(tabgaokao);
        tvMajorScore->setObjectName("tvMajorScore");
        tvMajorScore->setGeometry(QRect(410, 190, 391, 281));
        btnSchoolDetail = new QPushButton(tabgaokao);
        btnSchoolDetail->setObjectName("btnSchoolDetail");
        btnSchoolDetail->setGeometry(QRect(180, 100, 100, 32));
        tabWidget->addTab(tabgaokao, QString());
        tabMajor = new QWidget();
        tabMajor->setObjectName("tabMajor");
        label_5 = new QLabel(tabMajor);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(50, 30, 71, 16));
        cbYear = new QComboBox(tabMajor);
        cbYear->setObjectName("cbYear");
        cbYear->setGeometry(QRect(120, 25, 121, 32));
        label_6 = new QLabel(tabMajor);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(260, 30, 58, 16));
        edtMajor = new QLineEdit(tabMajor);
        edtMajor->setObjectName("edtMajor");
        edtMajor->setGeometry(QRect(320, 25, 251, 21));
        btnMajor = new QPushButton(tabMajor);
        btnMajor->setObjectName("btnMajor");
        btnMajor->setGeometry(QRect(600, 20, 100, 32));
        tvMajor = new QTableView(tabMajor);
        tvMajor->setObjectName("tvMajor");
        tvMajor->setGeometry(QRect(10, 60, 801, 401));
        tabWidget->addTab(tabMajor, QString());
        tabPlan = new QWidget();
        tabPlan->setObjectName("tabPlan");
        tvPlan = new QTableView(tabPlan);
        tvPlan->setObjectName("tvPlan");
        tvPlan->setGeometry(QRect(10, 60, 801, 401));
        label_7 = new QLabel(tabPlan);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(210, 30, 58, 16));
        cbPlanYear = new QComboBox(tabPlan);
        cbPlanYear->setObjectName("cbPlanYear");
        cbPlanYear->setGeometry(QRect(90, 25, 121, 32));
        edtPlanSchool = new QLineEdit(tabPlan);
        edtPlanSchool->setObjectName("edtPlanSchool");
        edtPlanSchool->setGeometry(QRect(260, 25, 181, 21));
        btnPlan = new QPushButton(tabPlan);
        btnPlan->setObjectName("btnPlan");
        btnPlan->setGeometry(QRect(710, 20, 100, 32));
        label_8 = new QLabel(tabPlan);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 30, 71, 16));
        label_9 = new QLabel(tabPlan);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(450, 30, 58, 16));
        edtPlanMajor = new QLineEdit(tabPlan);
        edtPlanMajor->setObjectName("edtPlanMajor");
        edtPlanMajor->setGeometry(QRect(500, 25, 181, 21));
        tabWidget->addTab(tabPlan, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 839, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(btnSearch, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::setFocus));
        QObject::connect(cbProvince, &QComboBox::currentIndexChanged, MainWindow, qOverload<>(&QMainWindow::setFocus));
        QObject::connect(btnMajor, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::setFocus));
        QObject::connect(btnPlan, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::setFocus));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\255\246\346\240\241\345\220\215\357\274\232", nullptr));
        leCollegeName->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\255\246\346\240\241\345\220\215", nullptr));
        btnSearch->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\237\216\345\270\202:", nullptr));
        cbProvince->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\347\234\201\344\273\275", nullptr));
        cbCity->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\345\237\216\345\270\202", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\255\246\346\240\241\347\261\273\345\236\213\357\274\232", nullptr));
        cbType->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\347\261\273\345\236\213", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\345\255\246\346\240\241\346\200\247\350\264\250", nullptr));
        cbTagsyl->setText(QCoreApplication::translate("MainWindow", "\345\217\214\344\270\200\346\265\201", nullptr));
        cbTag985->setText(QCoreApplication::translate("MainWindow", "985", nullptr));
        cbTag211->setText(QCoreApplication::translate("MainWindow", "211", nullptr));
        cbTagqjjh->setText(QCoreApplication::translate("MainWindow", "\345\274\272\345\237\272\350\256\241\345\210\222", nullptr));
        cbbxms->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\212\236\345\255\246\346\250\241\345\274\217", nullptr));
        cbzsms->setPlaceholderText(QCoreApplication::translate("MainWindow", "\346\213\233\347\224\237\346\250\241\345\274\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabcollegelist), QCoreApplication::translate("MainWindow", "\345\244\247\345\255\246\344\277\241\346\201\257", nullptr));
        lbIcon->setText(QString());
        lbCollegeName->setText(QCoreApplication::translate("MainWindow", "\345\244\247\345\255\246", nullptr));
        lbDangci->setText(QString());
        lbAbstract->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\275\225\345\217\226\345\210\206\346\225\260\347\272\277", nullptr));
        lbmajor->setText(QCoreApplication::translate("MainWindow", "\344\270\223\344\270\232\345\210\206\346\225\260\347\272\277", nullptr));
        btnSchoolDetail->setText(QCoreApplication::translate("MainWindow", "\345\255\246\346\240\241\350\257\246\346\203\205", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabgaokao), QCoreApplication::translate("MainWindow", "\345\244\247\345\255\246\346\213\233\347\224\237\350\257\246\346\203\205", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\345\275\225\345\217\226\345\271\264\344\273\275\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\344\270\223\344\270\232\345\220\215\357\274\232", nullptr));
        edtMajor->setInputMask(QString());
        edtMajor->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\344\270\223\344\270\232\345\220\215\357\274\214\346\224\257\346\214\201\346\250\241\347\263\212\346\237\245\350\257\242", nullptr));
        btnMajor->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabMajor), QCoreApplication::translate("MainWindow", "\344\270\223\344\270\232\345\275\225\345\217\226\346\203\205\345\206\265", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\345\255\246\346\240\241\345\220\215\357\274\232", nullptr));
        edtPlanSchool->setInputMask(QString());
        edtPlanSchool->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\255\246\346\240\241\345\220\215\357\274\214\346\224\257\346\214\201\346\250\241\347\263\212\346\237\245\350\257\242", nullptr));
        btnPlan->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\345\275\225\345\217\226\345\271\264\344\273\275\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\344\270\223\344\270\232\345\220\215\357\274\232", nullptr));
        edtPlanMajor->setInputMask(QString());
        edtPlanMajor->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\344\270\223\344\270\232\345\220\215\357\274\214\346\224\257\346\214\201\346\250\241\347\263\212\346\237\245\350\257\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabPlan), QCoreApplication::translate("MainWindow", "\346\213\233\347\224\237\350\256\241\345\210\222", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
