#ifndef FRMFILTEROPTION_H
#define FRMFILTEROPTION_H

#include <QWidget>
#include <QTableView>
#include <QMap>
#include <QStandardItem>

namespace Ui {
class FrmFilterOption;
}

class FrmFilterOption : public QWidget
{
    Q_OBJECT

public:
    explicit FrmFilterOption(QWidget *parent = nullptr);
    ~FrmFilterOption();

    void initList(QTableView *tableview,int colIndex);

    void treeItemChanged ( QStandardItem * item );
    void treeItem_checkAllChild(QStandardItem * item, bool check);
    void treeItem_checkAllChild_recursion(QStandardItem * item,bool check);

    Qt::CheckState checkSibling(QStandardItem * item);

private slots:
    void treeItem_CheckChildChanged(QStandardItem * item);
    void cancel_clicked();
    void confirm_clicked();
private:
    Ui::FrmFilterOption *ui;
    QTableView *table;
    int colIndex;
    QMap<QString,bool> fieldMap;

    //获取每个值的状态，需要遍历所有记录，效率比较低
    QMap<QString,bool> getFieldStatus(QTableView *tableview,int colIndex);

    void initTreeview(QMap<QString,bool> fieldMap);
};

#endif // FRMFILTEROPTION_H
