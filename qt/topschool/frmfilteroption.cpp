#include "frmfilteroption.h"
#include "ui_frmfilteroption.h"
#include <QStandardItemModel>
#include <QStandardItem>

FrmFilterOption::FrmFilterOption(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmFilterOption)
{
    ui->setupUi(this);
    connect(ui->btnOK,SIGNAL(clicked()),this,SLOT(confirm_clicked()));
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(cancel_clicked()));
}

FrmFilterOption::~FrmFilterOption()
{
    delete ui;
}

void FrmFilterOption::initList(QTableView *tableview,int colIndex)
{
    if(tableview)
    {
        this->fieldMap=getFieldStatus(tableview,colIndex);
        //遍历,生成清单
        initTreeview(fieldMap);
        this->colIndex=colIndex;
        this->table=tableview;
    }
}

QMap<QString,bool> FrmFilterOption::getFieldStatus(QTableView *tableview,int colIndex)
{
    QMap<QString,bool> fieldMap;

    for(int row=0;row<tableview->model()->rowCount();row++)
    {
        QString item=tableview->model()->index(row,colIndex).data().toString();
        if(tableview->isRowHidden(row))
        {
            fieldMap.insert(item,false);
        }
        else
        {
            fieldMap.insert(item,true);
        }
    }

    return fieldMap;
}

void FrmFilterOption::initTreeview(QMap<QString,bool> fieldMap)
{
    QStandardItemModel *model=new QStandardItemModel();
    connect ( model ,&QStandardItemModel::itemChanged , this ,&FrmFilterOption::treeItemChanged );

    QStandardItem * first=new QStandardItem("全选");
    model->appendRow(first);
    first->setCheckable(true);
    first->setAutoTristate(true);
//    first->setUserTristate(true);//复选框三态

    int selected=0;
    for(int i=0;i<fieldMap.keys().count();i++)
    {
        QStandardItem *section=new QStandardItem(fieldMap.keys().at(i));
        section->setCheckable(true);
//        section->setUserTristate(true);
        if(fieldMap.value(fieldMap.keys().at(i)))
        {
            section->setCheckState(Qt::Checked);
            selected++;
        }
        else
        {
            section->setCheckState(Qt::Unchecked);
        }

        first->appendRow(section);
        first->setChild(section->index().row(),0,section);
//        ui->treeView->resizeColumnToContents(0);
    }
    if(selected==0)
        first->setCheckState(Qt::Unchecked);
    if(selected==fieldMap.keys().count())
        first->setCheckState(Qt::Checked);
    else
        first->setCheckState(Qt::PartiallyChecked);

    ui->treeView->setHeaderHidden(true);
//    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->treeView->header()->setStretchLastSection(true);
    ui->treeView->setModel(model);
//    ui->treeView->setAutoMode(AutoTristateTreeView::AutoTristateMode);
//    connect(ui->treeView, &AutoTristateTreeView::tristate_changed_, this, &QWidget::tristate_changed_);
    ui->treeView->expandAll();
    ui->treeView->resizeColumnToContents(0);
}

//父子节点复选框自动关联实现
void FrmFilterOption::treeItemChanged( QStandardItem * item )
{
    if(item==nullptr)
    {
        return;
    }
    if ( item->isCheckable())
    {
        //如果条目是存在复选框的，那么就进行下面的操作
        Qt::CheckState state=item->checkState();
        if(item->isAutoTristate())
        {
            //如果条目是三态的，说明可以对子目录进行全选和全不选的设置
            if ( state != Qt::PartiallyChecked )
            {
                //当前是选中状态，需要对其子项目进行全选
                treeItem_checkAllChild ( item , state == Qt::Checked ? true : false );
            }
        }
        else
        {
            //说明是两态的，两态会对父级的三态有影响
            //判断兄弟节点的情况
            treeItem_CheckChildChanged ( item );
        }

        //记录选中项。。。。。。。
//       qDebug()<<item->text()<<item->parent();
       if(item->parent())
       {
           //子节点
           if(item->checkState()==Qt::Checked)
           {
                this->fieldMap[item->text()]=true;
           }
           else
           {
               this->fieldMap[item->text()]=false;
           }
       }
       else
       {
           //根节点
           if(item->checkState()==Qt::Checked)
           {
               for(int i=0;i<this->fieldMap.keys().count();i++)
               {
                   this->fieldMap[this->fieldMap.keys().at(i)]=true;
               }
           }
       }
    }
}

//递归设置所有的子项目为全选或全不选状态
void FrmFilterOption::treeItem_checkAllChild(QStandardItem * item, bool check)
{
    if(item==nullptr)
    {
        return;
    }
    int rowCount = item->rowCount();
    for(int i=0;i<rowCount;++i)
    {
        QStandardItem* childItems = item->child(i);
        treeItem_checkAllChild_recursion(childItems,check);
    }
    if(item->isCheckable())
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}

void FrmFilterOption::treeItem_checkAllChild_recursion(QStandardItem * item,bool check)
{
    if(item==nullptr)
    {
        return;
    }
    int rowCount = item->rowCount();
    for(int i=0;i<rowCount;++i)
    {
        QStandardItem* childItems = item->child(i);
        treeItem_checkAllChild_recursion(childItems,check);
    }
    if(item->isCheckable())
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}

//根据子节点的改变，更改父节点的选择情况
void FrmFilterOption::treeItem_CheckChildChanged(QStandardItem * item)
{
    if(item==nullptr)
    {
        return;
    }
    Qt::CheckState siblingState = checkSibling(item);
    QStandardItem * parentItem = item->parent();
    if(nullptr == parentItem)
        return;
    if(Qt::PartiallyChecked == siblingState)
    {
        if(parentItem->isCheckable() && parentItem->isAutoTristate())
            parentItem->setCheckState(Qt::PartiallyChecked);
    }
    else if(Qt::Checked == siblingState)
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Checked);
    }
    else{
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Unchecked);
    }
    treeItem_CheckChildChanged(parentItem);
}

//测量兄弟节点的情况，如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
//如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
Qt::CheckState FrmFilterOption::checkSibling(QStandardItem * item)
{
    //先通过父节点获取兄弟节点
    QStandardItem * parent = item->parent();
    if(nullptr == parent)
    {
        return item->checkState();
    }

    int brotherCount = parent->rowCount();
    int checkedCount(0),unCheckedCount(0);
    Qt::CheckState state;
    for(int i=0;i<brotherCount;++i)
    {
        QStandardItem* siblingItem = parent->child(i);
        state = siblingItem->checkState();
        if(Qt::PartiallyChecked == state)
            return Qt::PartiallyChecked;
        else if(Qt::Unchecked == state)
            ++unCheckedCount;
        else
            ++checkedCount;
        if(checkedCount>0 && unCheckedCount>0)
            return Qt::PartiallyChecked;
    }
    if(unCheckedCount>0)
        return Qt::Unchecked;
    return Qt::Checked;
}

void FrmFilterOption::cancel_clicked()
{
    this->close();
}

void FrmFilterOption::confirm_clicked()
{
    if(this->table)
    {
//        qDebug()<<ui->treeView->model()->rowCount();
        //遍历数据表
        for(int row=0;row<this->table->model()->rowCount();row++)
        {
            QString item=this->table->model()->index(row,colIndex).data().toString();
            this->table->setRowHidden(row,!this->fieldMap[item]);
        }
    }
    this->close();
}
