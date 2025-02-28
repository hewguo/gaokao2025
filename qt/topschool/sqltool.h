#ifndef SQLTOOL_H
#define SQLTOOL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include <QDir>
#include <QSqlRecord>
#include <qhash.h>

class SQLTOOL
{
public:
    SQLTOOL(const QString &str,const QString &password,const QString &port,const QString &host, const QString &username);
    ~SQLTOOL();
public:

    //创建数据库并建立连接
    bool OpenDb(void);
    //查询当前表的触发器数量
    int getTriggerCount(const QString &name);
    //查询当前表的视图数量
    int getViewCount(const QString &name);
    //获取当前表属性
    QList<QString> propertyOfDatabase(const QString &tablename);
    //查询数据库中表的数量
    int numOfDatabase(void);
    //查询数据库中的表名
    QList<QString> namesOfDatabase(void);
    //查询当前表中所有的字段名
    QList<QString> getNameFromTable(const QString &name);
    //查询数据库中当前表的所有字段
    QList<QString> selectFromTable(const QString &name);

    int dataSizeoftable(const QString &name);

    QList<QString> selectFromCols(const QString &tablename, const QString &colname);

    //开启事务执行数据库更新
    bool appendData(const QList<QString> &data,const QString &tablename);

    //执行更新语句
    int updateTable(const QString &tablename, const QString &colname, const QString &val,const QString &pk,const QString &pkval);

    //增加执行语句
    int InsertIntoTable(const QString &sql);

    //批量插入语句
    bool execbathInsert(const QList<QStringList> &para);


    //返回当前数据库中所有数据表名、字段名以及对应的数据
    //void sendPara(QMultiHash<QList<QString>, QMultiHash<QList<QString>, QList<QString>>> para);
    QHash<QString, QHash<QString,QList<QString>>> getAllInfo();

    QHash<QString, QList<QString>> getTablesandCols();

    //根据sql获取数据集
    QJsonDocument selectDataFromSQL(const QString& strSql);
    //创建数据表（student）
    void createTable(void);
    //在表格中增加新的字段
    void addNewcolumn(QString &columnNameAndproperty);
    //查询和显示结果
    void queryTable(QString& str);
    //判断数据表是否存在
    bool IsTaBexists(QString& Tabname);
    //插入数据
    void singleinsertdata(QString &singledb);//插入单条数据
    void Moreinsertdata(QList<QString> &moredb);//插入多条数据
    //删除数据
    bool deletedata(const QString &name,QList<QString>,QList<QString>);
    //修改数据
    void updatedata();
    //关闭数据库
    void closeDb(void);
private:
    QSqlDatabase db;//用于建立和数据库的连接
    QString connName;

};


#endif // SQLTOOL_H
