#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QPixmap>
#include <QDir>
#include <QLabel>
#include "customsqltablemodel.h"
#include <QHeaderView>
#include "commontools.h"
#include <QTableWidget>
#include "frmfilteroption.h"
#include "frmschooldetial.h"
#include <QToolTip>
#include <QBuffer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->resize(839,583);

    sqltool=new SQLTOOL("gaokao2025.sqlite","","","","");

    sqltool->OpenDb();

    fillProvince();
    fillType();
    fillBxms();
    fillZsms();
    fillYear();
    fillPlanYear();

    autoResize();

    ui->tvCollegeData->setAlternatingRowColors(true);
    ui->tvMajorScore->setAlternatingRowColors(true);
    ui->tvSchoolScore->setAlternatingRowColors(true);
    ui->tvMajor->setAlternatingRowColors(true);
    ui->tvPlan->setAlternatingRowColors(true);

    //鼠标悬停事件
    ui->tvCollegeData->setMouseTracking(true);
    connect(ui->tvCollegeData,SIGNAL(entered(QModelIndex)),this,SLOT(showBigIconFromTable(QModelIndex)));

//    ui->tvCollegeData->setStyleSheet("alternate-background-color:rgb(11,231,255);background-color:QPalette::Base");
    //行选择
    ui->tvCollegeData->setSelectionBehavior(QAbstractItemView::SelectRows);
    //双击事件连接
    connect(ui->tvCollegeData,SIGNAL(doubleClicked(const QModelIndex)),this,SLOT(rowDoubleClicked(const QModelIndex)));

    connect(ui->tvMajorScore,SIGNAL(doubleClicked(const QModelIndex)),this,SLOT(tvMajorScoreDoubleClicked(const QModelIndex)));
    connect(ui->tvMajor,SIGNAL(doubleClicked(const QModelIndex)),this,SLOT(tvMajorDoubleClicked(const QModelIndex)));
    ui->tabWidget->setCurrentWidget(ui->tabcollegelist);

    this->setWindowIcon(QIcon(":/jpg/logo.ico"));
    this->setWindowIconText("高考志愿填报-浙江版2025");
    this->setWindowTitle("高考志愿填报-浙江版2025");

    connect(ui->btnSchoolDetail,SIGNAL(clicked(bool)),this,SLOT(on_btnSchoolDetail_clicked()));

    this->setWindowState(Qt::WindowMaximized);


}


MainWindow::~MainWindow()
{
    delete ui;
    sqltool->closeDb();

}

void MainWindow::autoResize()
{
    ui->tabWidget->resize(ui->centralwidget->size());
    ui->tvCollegeData->resize(ui->centralwidget->geometry().width()-20,ui->centralwidget->geometry().height()-150);
    // 设置表格调整模式为适应表格内容
    ui->tvCollegeData->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // 设置最小的宽度
    ui->tvCollegeData->horizontalHeader()->setMinimumSectionSize(30);
    ui->tvCollegeData->horizontalHeader()->setMaximumSectionSize(300);

    int width=ui->centralwidget->geometry().width();
    int height=ui->centralwidget->geometry().height();
    ui->lbmajor->setGeometry(width/2+10,ui->lbmajor->geometry().y(),ui->lbmajor->geometry().width(),ui->lbmajor->geometry().height());
    ui->tvSchoolScore->setGeometry(10,190,width/2-15,height-220);
    ui->tvMajorScore->setGeometry(width/2+5,190,width/2-15,height-220);

    ui->tvSchoolScore->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tvMajorScore->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tvMajor->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tvPlan->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tvMajor->setGeometry(10,60,width-20,height-90);
    ui->tvPlan->setGeometry(10,60,width-20,height-90);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    autoResize();
}

void MainWindow::on_btnSearch_clicked()
{

    QString strName=ui->leCollegeName->text();

    CustomSqlTableModel *model = new CustomSqlTableModel(this);

    // QString strSql="select '' as logo1,college_name,uniqueRank,abstract1,abstract2,'' as taglogo,tag,batch,character,city,logo,abstract from college_info where 1=1 ";
    QString strSql="select '' as logo1,college_name,uniqueRank,nature,education,'' as taglogo,tag,batch,city,logo from college_info where 1=1 ";

    if(!ui->leCollegeName->text().isEmpty())
    {
        strSql+="and college_name like '%"+ui->leCollegeName->text()+"%' ";
    }

    if(ui->cbProvince->currentIndex()>0)
    {
        strSql+="and province='"+ui->cbProvince->currentText()+"' ";
    }

    if(ui->cbCity->currentIndex()>0)
    {
        strSql+="and city='"+ui->cbCity->currentText()+"' ";
    }
    if(ui->cbType->currentIndex()>0)
    {
        strSql+="and school_type='"+ui->cbType->currentText()+"' ";
    }

    //强基、985、211、双一流
    QString tag="";
    if(ui->cbTagsyl->isChecked())
    {
        tag=" tag like '%双一流%' ";
    }
    if(ui->cbTag985->isChecked())
    {
        if(!tag.isEmpty())
        {
            tag+=" or ";
        }
        tag+=" tag like '%985%' ";
    }
    if(ui->cbTag211->isChecked())
    {
        if(!tag.isEmpty())
        {
            tag+=" or ";
        }
        tag+=" tag like '%211%' ";
    }
    if(ui->cbTagqjjh->isChecked())
    {
        if(!tag.isEmpty())
        {
            tag+=" or ";
        }
        tag+=" tag like '%强基计划%' ";
    }
    if(!tag.isEmpty()){
        strSql+=" and"+tag;
    }

    if(ui->cbbxms->currentIndex()>0)
    {
        strSql+="and nature='"+ui->cbbxms->currentText()+"' ";
    }
    if(ui->cbzsms->currentIndex()>0)
    {
        strSql+="and education='"+ui->cbzsms->currentText()+"' ";
    }


    strSql+=" order by cast(rank as int)";
//=========================================='' as logo1,college_name,uniqueRank,nature,education,'' as taglogo,tag,batch,city,logo
    //======================================'' as logo1,college_name,uniqueRank,abstract1,abstract2,'' as taglogo,tag,batch,character,city,logo,abstract
    model->setQuery(strSql);
    model->setHeaderData(0,Qt::Horizontal,tr(""));
    model->setHeaderData(1,Qt::Horizontal,tr("大学"));
    model->setHeaderData(2,Qt::Horizontal,tr("排名"));
    model->setHeaderData(3,Qt::Horizontal,tr("办学模式"));
    model->setHeaderData(4,Qt::Horizontal,tr("招生"));
    model->setHeaderData(5,Qt::Horizontal,tr("学校档次"));
    model->setHeaderData(6,Qt::Horizontal,tr("学校档次1"));
    model->setHeaderData(7,Qt::Horizontal,tr("批次"));
    model->setHeaderData(8,Qt::Horizontal,tr("城市"));
    model->setHeaderData(9,Qt::Horizontal,tr("logo"));
    //model->setHeaderData(11,Qt::Horizontal,tr("概要"));

    ui->tvCollegeData->setModel(model);

    ui->tvCollegeData->show();

    ui->tvCollegeData->hideColumn(6);
    ui->tvCollegeData->hideColumn(9);
    // ui->tvCollegeData->hideColumn(8);
    // ui->tvCollegeData->hideColumn(10);

    ui->tvCollegeData->setIconSize(QSize(30,30));

}
//ok
void MainWindow::fillProvince()
{
    QString strSQL="select distinct province from college_info";
    QJsonDocument json=sqltool->selectDataFromSQL(strSQL);
    QJsonArray     recordsArray=json.array();

    ui->cbProvince->clear();
    ui->cbCity->clear();
    ui->cbCity->setEnabled(false);
    ui->cbProvince->addItem("ALL");

    for(QJsonArray::iterator it=recordsArray.begin();it!=recordsArray.end();++it)
    {
        QJsonObject recordObject=it->toObject();
        if(!recordObject["province"].toString().isEmpty())
        {
            ui->cbProvince->addItem(recordObject["province"].toString());
        }
    }

}
//ok
void MainWindow::fillCity()
{
    QString province=ui->cbProvince->currentText();
    int provinceIndex=ui->cbProvince->currentIndex();
    if(provinceIndex>0)
    {
        QString strSQL="select distinct city from college_info where province='"+province+"'";

        QJsonDocument json=sqltool->selectDataFromSQL(strSQL);
        QJsonArray     recordsArray=json.array();

        ui->cbCity->clear();
        ui->cbCity->addItem("ALL");

        for(QJsonArray::iterator it=recordsArray.begin();it!=recordsArray.end();++it)
        {
            QJsonObject recordObject=it->toObject();
            if(!recordObject["city"].toString().isEmpty())
            {
                ui->cbCity->addItem(recordObject["city"].toString());
            }
        }
        ui->cbCity->setEnabled(true);
    }
}
//ok
void MainWindow::fillType()
{
    QString strSQL="select distinct school_type from college_info";
    QJsonDocument json=sqltool->selectDataFromSQL(strSQL);
    QJsonArray     recordsArray=json.array();

    ui->cbType->clear();
    ui->cbType->addItem("ALL");

    for(QJsonArray::iterator it=recordsArray.begin();it!=recordsArray.end();++it)
    {
        QJsonObject recordObject=it->toObject();
        if(!recordObject["school_type"].toString().isEmpty())
        {
            ui->cbType->addItem(recordObject["school_type"].toString());
        }
    }
}
//ok
void MainWindow::fillBxms()
{
    QString strSQL="select distinct nature from college_info";
    QJsonDocument json=sqltool->selectDataFromSQL(strSQL);
    QJsonArray     recordsArray=json.array();

    ui->cbbxms->clear();
    ui->cbbxms->addItem("ALL");

    for(QJsonArray::iterator it=recordsArray.begin();it!=recordsArray.end();++it)
    {
        QJsonObject recordObject=it->toObject();
        if(!recordObject["nature"].toString().isEmpty())
        {
            ui->cbbxms->addItem(recordObject["nature"].toString());
        }
    }

}
//ok
void MainWindow::fillZsms()
{
    QString strSQL="select distinct education from college_info";
    QJsonDocument json=sqltool->selectDataFromSQL(strSQL);
    QJsonArray     recordsArray=json.array();

    ui->cbzsms->clear();
    ui->cbzsms->addItem("ALL");

    for(QJsonArray::iterator it=recordsArray.begin();it!=recordsArray.end();++it)
    {
        QJsonObject recordObject=it->toObject();
        if(!recordObject["education"].toString().isEmpty())
        {
            ui->cbzsms->addItem(recordObject["education"].toString());
        }
    }

}
//ok
void MainWindow::fillYear()
{
    QString strSQL="select distinct year from majorscore";
    QJsonDocument json=sqltool->selectDataFromSQL(strSQL);
    QJsonArray     recordsArray=json.array();

    ui->cbYear->clear();
    ui->cbYear->addItem("ALL");
    for(QJsonArray::iterator it=recordsArray.begin();it!=recordsArray.end();++it)
    {
        QJsonObject recordObject=it->toObject();
        if(!recordObject["year"].toString().isEmpty())
        {
            ui->cbYear->addItem(recordObject["year"].toString());
        }
    }

}
//ok
void MainWindow::fillPlanYear()
{
    QString strSQL="select distinct year from college_plan";
    QJsonDocument json=sqltool->selectDataFromSQL(strSQL);
    QJsonArray     recordsArray=json.array();

    ui->cbPlanYear->clear();
    ui->cbPlanYear->addItem("ALL");
    for(QJsonArray::iterator it=recordsArray.begin();it!=recordsArray.end();++it)
    {
        QJsonObject recordObject=it->toObject();
        if(!recordObject["year"].toString().isEmpty())
        {
            ui->cbPlanYear->addItem(recordObject["year"].toString());
        }
    }
}

void MainWindow::on_cbProvince_currentIndexChanged(int index)
{
    ui->cbCity->setEnabled(false);
    fillCity();
}
//ok
void MainWindow::getSchoolDetail(QString school_id)
{
    QString strSQL="select detail from college_detail where name='"+school_id+"'";
    QJsonDocument json=sqltool->selectDataFromSQL(strSQL);
    QJsonArray     recordsArray=json.array();
    QString schoolDetail="简介";
    if(!recordsArray.isEmpty())
    {
        QJsonObject recordObject=recordsArray[0].toObject();
        schoolDetail=recordObject["detail"].toString();
    }
    //显示popup窗口
    FrmSchoolDetial *frmSchoolDetial=new FrmSchoolDetial(schoolDetail,this);
    frmSchoolDetial->show();

}

void MainWindow::on_btnSchoolDetail_clicked()
{
    //点击学校详情按钮
    QString schoolName=ui->lbCollegeName->text();
    getSchoolDetail(schoolName);
}
//ok
void MainWindow::rowDoubleClicked(const QModelIndex idx)
{
    if(idx.isValid()&&idx.row()>=0)
    {

        QPixmap pix=CommonTools::getPixFromBase64(idx,9);//获取第9列图标数据

        ui->lbIcon->setPixmap(pix.scaled(120,120,Qt::KeepAspectRatio));

        //学校名字
        QModelIndex nameIndex=idx.model()->index(idx.row(),1);
        QString name=nameIndex.data().toString();
        ui->lbCollegeName->setText(name);

        //显示学校介绍
//        getSchoolDetail(name);

        //学校档次
        QPixmap pixDangci=CommonTools::getPixFromLogo(idx,6);
        int height=20;
        int width=pixDangci.width()*height/pixDangci.height();
        ui->lbDangci->setGeometry(180,130,width+4,height+4);
        ui->lbDangci->setPixmap(pixDangci.scaled(width,height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

        QModelIndex abstractIndex=idx.model()->index(idx.row(),11);
        ui->lbAbstract->setText(abstractIndex.data().toString());

        //查询学校录取分数线
        QSqlQueryModel *schoolModel = new QSqlQueryModel(this);
        QString strSql="select year,batchName||'/'||enrollType,minScore||'/'||minScoreOrder,minCha,curriculum ";
        strSql+="from schoolscore where legalName='"+name+"' order by year desc";
        schoolModel->setQuery(strSql);
        schoolModel->setHeaderData(0,Qt::Horizontal,tr("年份"));
        schoolModel->setHeaderData(1,Qt::Horizontal,tr("批次/招生类型"));
        schoolModel->setHeaderData(2,Qt::Horizontal,tr("最低分/位次"));
        schoolModel->setHeaderData(3,Qt::Horizontal,tr("最低分差"));
        schoolModel->setHeaderData(4,Qt::Horizontal,tr("科目"));
        ui->tvSchoolScore->setModel(schoolModel);
        //设置表头过滤
        QHeaderView *header=ui->tvSchoolScore->horizontalHeader();
        header->setSectionsClickable(true);

        connect(header,SIGNAL(sectionDoubleClicked(int)),SLOT(onHeaderFilterData(int)));

        ui->tvSchoolScore->show();

        //查询专业分数线
        QSqlQueryModel *majorModel = new QSqlQueryModel(this);
        strSql="select year,majorName,specialCourse,minScore||'/'||minScoreOrder,batchName ";
        strSql+= "from majorscore where legalName='"+name+"' order by year desc";
        majorModel->setQuery(strSql);
        majorModel->setHeaderData(0,Qt::Horizontal,tr("年份"));
        majorModel->setHeaderData(1,Qt::Horizontal,tr("专业"));
        majorModel->setHeaderData(2,Qt::Horizontal,tr("选课要求"));
        majorModel->setHeaderData(3,Qt::Horizontal,tr("最低分/位次"));
        majorModel->setHeaderData(4,Qt::Horizontal,tr("批次"));
        ui->tvMajorScore->setModel(majorModel);

        //设置表头过滤
        QHeaderView *majorHeader=ui->tvMajorScore->horizontalHeader();
        majorHeader->setSectionsClickable(true);

        connect(majorHeader,SIGNAL(sectionDoubleClicked(int)),SLOT(onHeaderFilterData(int)));

        ui->tvMajorScore->show();


        ui->tabWidget->setCurrentWidget(ui->tabgaokao);

    }

}

void MainWindow::onHeaderFilterData(int AColumn)
{
    QHeaderView *header = qobject_cast<QHeaderView *>(sender());
    QTableView *table = header!=NULL ? qobject_cast<QTableView *>(header->parentWidget()) : NULL;
    if(table)
    {
        FrmFilterOption *frmFilterOption=new FrmFilterOption();
        frmFilterOption->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
        int x=(QCursor().pos()).x();
        int y=(QCursor().pos()).y()+5;

        frmFilterOption->setGeometry(QRect(x,y,frmFilterOption->geometry().width(),frmFilterOption->geometry().height()));

        frmFilterOption->initList(table,AColumn);

        frmFilterOption->show();
    }
    if(header)
    {
//        qDebug()<<AColumn;
   }
}

//ok
void MainWindow::on_btnMajor_clicked()
{
    //专业分数查询按钮
    QString strSql="select year,legalName,majorName,specialCourse,minScore||'/'||minScoreOrder,batchName from majorscore where 1=1";
    if(ui->cbYear->currentIndex()>=1)
    {
        strSql+=" and year='"+ui->cbYear->currentText()+"' ";
    }

    strSql+= " and majorName like '%"+ui->edtMajor->text()+"%' order by year desc,minScore desc";

    QSqlQueryModel *majorModel = new QSqlQueryModel(this);

    majorModel->setQuery(strSql);
    majorModel->setHeaderData(0,Qt::Horizontal,tr("年份"));
    majorModel->setHeaderData(1,Qt::Horizontal,tr("学校"));
    majorModel->setHeaderData(2,Qt::Horizontal,tr("专业"));
    majorModel->setHeaderData(3,Qt::Horizontal,tr("选课要求"));
    majorModel->setHeaderData(4,Qt::Horizontal,tr("最低分/位次"));
    majorModel->setHeaderData(5,Qt::Horizontal,tr("批次"));
    ui->tvMajor->setModel(majorModel);

    ui->tvMajor->show();
}

//ok
void MainWindow::on_btnPlan_clicked()
{
    //查看计划录取数
    //专业分数查询按钮
    // QString strSql="select year,name,spname||'/'||level2_name as spname,num,length,tuition,sp_info,local_type_name||'/'||local_batch_name as type_name from college_plan where 1=1";
    QString strSql="select year,legalName,major_name as spname,college_plan.enroll_num as num,college_plan.lengthOfSchooling as length,tuition,college_plan.selectSubjects as sp_info,batch_name as type_name from college_plan where 1=1";
    if(ui->cbPlanYear->currentIndex()>=1)
    {
        strSql+=" and year='"+ui->cbPlanYear->currentText()+"' ";
    }
    strSql+=" and major_name like '%"+ui->edtPlanMajor->text()+"%' ";
    strSql+= " and legalName like '%"+ui->edtPlanSchool->text()+"%'  order by id ,year desc";

    QSqlQueryModel *majorModel = new QSqlQueryModel(this);

    majorModel->setQuery(strSql);
    majorModel->setHeaderData(0,Qt::Horizontal,tr("年份"));
    majorModel->setHeaderData(1,Qt::Horizontal,tr("学校"));
    majorModel->setHeaderData(2,Qt::Horizontal,tr("专业"));
    majorModel->setHeaderData(3,Qt::Horizontal,tr("计划招生"));
    majorModel->setHeaderData(4,Qt::Horizontal,tr("学制"));
    majorModel->setHeaderData(5,Qt::Horizontal,tr("学费"));
    majorModel->setHeaderData(6,Qt::Horizontal,tr("选科要求"));
    majorModel->setHeaderData(7,Qt::Horizontal,tr("批次"));

    ui->tvPlan->setModel(majorModel);

    ui->tvPlan->setColumnWidth(2,600);
    ui->tvPlan->resizeColumnToContents(0);
    ui->tvPlan->resizeColumnToContents(1);
    ui->tvPlan->resizeColumnToContents(3);
    ui->tvPlan->resizeColumnToContents(4);
    ui->tvPlan->resizeColumnToContents(5);
    ui->tvPlan->resizeColumnToContents(6);
    ui->tvPlan->resizeColumnToContents(7);

    ui->tvPlan->resizeRowsToContents();

    ui->tvPlan->show();

}

void MainWindow::showBigIconFromTable(QModelIndex index)
{
    if(index.column()==0)
    {
        QPixmap pix=CommonTools::getPixFromBase64(index,9);
        QImage icon=(pix.scaled(200,200,Qt::KeepAspectRatio)).toImage();
        QByteArray data;
        QBuffer buffer(&data);
        icon.save(&buffer, "PNG", 100);

        QString html = QString("<img src='data:image/png;base64, %0'>").arg(QString(data.toBase64()));
        QToolTip::showText(QCursor::pos(),html,this,QRect(),10000);

    }
    return;
}

//双击后跳转到专业录取情况
void MainWindow::tvMajorScoreDoubleClicked(const QModelIndex idx)
{
    //
    if(idx.isValid()&&idx.row()>=0)
    {
        QModelIndex majorNameIndex=idx.model()->index(idx.row(),1);
        QString majorName=majorNameIndex.data().toString();

        ui->edtMajor->setText(majorName);
        this->on_btnMajor_clicked();

        ui->tabWidget->setCurrentWidget(ui->tabMajor);
    }
}

//双击后跳转到招生计划
void MainWindow::tvMajorDoubleClicked(const QModelIndex idx)
{
    //
    if(idx.isValid()&&idx.row()>=0)
    {
        QModelIndex majorNameIndex=idx.model()->index(idx.row(),2);
        QString majorName=majorNameIndex.data().toString();

        QModelIndex nameIndex=idx.model()->index(idx.row(),1);
        QString name=nameIndex.data().toString();

        ui->edtPlanMajor->setText(majorName);
        ui->edtPlanSchool->setText(name);

        this->on_btnPlan_clicked();

        ui->tabWidget->setCurrentWidget(ui->tabPlan);
    }
}

