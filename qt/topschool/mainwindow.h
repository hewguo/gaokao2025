#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sqltool.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSearch_clicked();

    void on_cbProvince_currentIndexChanged(int index);

    void rowDoubleClicked(const QModelIndex idx);

    //点击表头筛选数据
    void onHeaderFilterData(int AColumn);


    void on_btnMajor_clicked();

    void on_btnPlan_clicked();

    //处理表格鼠标悬停事件，当鼠标在图标列时显示大图标
    void showBigIconFromTable(QModelIndex index);
    //双击后跳转到专业录取情况
    void tvMajorScoreDoubleClicked(const QModelIndex idx);
    //双击后跳转到招生计划
    void tvMajorDoubleClicked(const QModelIndex idx);

    //点击学校详情按钮
    void on_btnSchoolDetail_clicked();

private:
    Ui::MainWindow *ui;
    SQLTOOL *sqltool;

    //填充省份
    void fillProvince();
    //取得城市信息并填充
    void fillCity();
    //填充学校类型
    void fillType();
    //办学模式
    void fillBxms();
    //招生模式
    void fillZsms();
    //填充招生年份
    void fillYear();
    //填充计划招生年份
    void fillPlanYear();

    //调整尺寸
    void autoResize();
    //根据学校id获取学校详情
    void getSchoolDetail(QString school_id);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
};
#endif // MAINWINDOW_H
