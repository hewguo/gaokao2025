#include "sqltool.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QCoreApplication>

SQLTOOL::SQLTOOL(const QString &str,
                 const QString &password,
                const QString &port,
                const QString &host,
                const QString &username)
{
    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        this->connName="sqliteConnection";
        //建立和sqlite数据的连接
        this->db = QSqlDatabase::addDatabase("QSQLITE");
        //设置数据库文件的名字
//        QString dbname =  str;
//        this->db.setDatabaseName(dbname);
        this->db.setDatabaseName(QCoreApplication::applicationDirPath()+"/"+str);
//        qDebug()<<this->db.databaseName();
        /*this->db.setPassword(password);
        this->db.setPort(port.toInt());
        this->db.setHostName(host);
        this->db.setUserName(username);*/
    }
}
/*析构函数关闭数据库连接*/
SQLTOOL::~SQLTOOL()
{
    this->db.removeDatabase(this->db.connectionName());
    this->db.close();


}

//打开数据库
bool SQLTOOL::OpenDb(void)
{
    //打开数据库
    if (this->db.open() == false) {
        qDebug() << "fail to connect！";
        return false;
    }
    qDebug() << "successful!";
    return true;
}

//获取当前表属性
QList<QString> SQLTOOL::propertyOfDatabase(const QString &tablename)
{
    QSqlQuery query;
    QList<QString> tempList;
    query.exec(QString("PRAGMA table_info('%1')").arg(tablename));

    QSqlRecord rec =  query.record();
    int cols = rec.count();
    for (int i = 0; i < cols; i++)
    {
        tempList.append(rec.fieldName(i));
        //qDebug() << rec.fieldName(i);
    }

    return tempList;
}

//查询数据库中表数量
int SQLTOOL::numOfDatabase(void)
{
    QSqlQuery query=QSqlQuery(this->db);

    query.exec("select count(1) from sqlite_master where type in('table');");
    if (query.first()) {
        return query.value(0).toInt();
    }
    return -1;
}

//查询数据库中表名
QList<QString> SQLTOOL::namesOfDatabase(void)
{
    QSqlQuery query;
    QList<QString> result;
    query.exec("select name from sqlite_master");
    int count = 0;
    while (query.next())
    {
        //qDebug()<<query.value(0).toString();
        result.append(query.value(0).toString());
    }
    return result;
}

//查询数据库中当前表的所有字段
QList<QString> SQLTOOL::selectFromTable(const QString &name)
{
    QSqlQuery query;
    QList<QString> result;
    query.exec(QString("select * from %1").arg(name));

    QSqlRecord rec = query.record();

    QList<QString> names;
    names = getNameFromTable(name);

    for (int r = 0; query.next(); r++)
        for (int c = 0; c < rec.count(); c++) {
            //qDebug() << QString("Row %1, %2: %3").arg(r).arg(rec.fieldName(c)).arg(query.value(c).toString());
            //qDebug() << rec.fieldName(c);
            if (names.contains(rec.fieldName(c))) {
                result.append(query.value(c).toString());
            }
        }
    return result;
}

//
QList<QString> SQLTOOL::getNameFromTable(const QString &name)
{
    QSqlQuery query;
    QList<QString> result;
    query.exec(QString("select * from %1").arg(name));
    QSqlRecord rec = query.record();
    for (int c = 0; c < rec.count(); c++) {
        //qDebug() << QString("Row %1, %2: %3").arg(r).arg(rec.fieldName(c)).arg(query.value(c).toString());
        //qDebug() << rec.fieldName(c);
        result.append(rec.fieldName(c));

    }
    return result;
}

//查询当前表中所含触发器数量
int SQLTOOL::getTriggerCount(const QString &name)
{
    QSqlQuery query;
    query.exec(QString(" SELECT name FROM sqlite_master WHERE type = 'trigger' AND tbl_name = '%1';").arg(name));
    if (query.first())
    {
        return query.value(0).toInt();
    }
    else
    {
        return 0;
    }
}
//查询当前表中所含视图数量
int SQLTOOL::getViewCount(const QString &name)
{
    QSqlQuery query;
    query.exec(QString(" SELECT name FROM sqlite_master WHERE type = 'view' AND tbl_name = '%1';").arg(name));
    if (query.first())
    {
        if (query.value(0).isNull())
        {
            return 0;
        }
        //qDebug() << query.value(0);
        return query.value(0).toInt();
    }
    else
    {
        return 0;
    }
}

void SQLTOOL::closeDb()
{

    this->db.removeDatabase(this->db.connectionName());
    this->db.close();
}

QList<QString> SQLTOOL::selectFromCols(const QString &tablename,const QString &colname)
{
    QSqlQuery query;
    QList<QString> result;
    query.exec(QString(
        "SELECT %1 FROM %2"
    ).arg(colname, tablename));
    QSqlRecord rec = query.record();



    for (int r = 0; query.next(); r++)
        for (int c = 0; c < rec.count(); c++) {
            //qDebug() << QString("Row %1, %2: %3").arg(r).arg(rec.fieldName(c)).arg(query.value(c).toString());
            //qDebug() << rec.fieldName(c);
            if (colname == rec.fieldName(c)) {
                result.append(query.value(c).toString());
            }
        }
    return result;
}


QHash<QString, QHash<QString, QList<QString>>> SQLTOOL::getAllInfo()
{
    QList<QString> tableInDataBase  = this->namesOfDatabase();
    QHash<QString, QHash<QString, QList<QString>>> result;
    /*for (auto &itor : tableInDataBase)
    {
        QList<QString> nameInTable = this->getNameFromTable(itor);
        QList<QString> dataUnderName = this->selectFromTable(itor);
        colsAnddata.insert(nameInTable, dataUnderName);
    }*/


    for (int i=0; i < tableInDataBase.size(); i++)
    {
        QList<QString> nameInTable = this->getNameFromTable(tableInDataBase.at(i));
        QHash<QString, QList<QString>> temphash;
        for (int j = 0; j < nameInTable.size(); j++)
        {
            QList<QString> data = this->selectFromCols(tableInDataBase.at(i), nameInTable.at(j));

            temphash.insert(nameInTable.at(j), data);

        }
        result.insert(tableInDataBase.at(i), temphash);

    }

    return result;
}

QHash<QString, QList<QString>> SQLTOOL::getTablesandCols()
{
    QList<QString> tables = this->namesOfDatabase();
    QHash<QString, QList<QString>> values;
    QList<QString> cols;
    for (int i = 0; i < tables.size(); i++)
    {
        QList<QString> cols = this->getNameFromTable(tables.at(i));
        values.insert(tables.at(i), cols);

    }

    return values;
}

QJsonDocument SQLTOOL::selectDataFromSQL(const QString& strSql)
{
    this->db.open();
    QSqlQuery query=QSqlQuery(this->db);
    if(query.exec(strSql)){
        QJsonDocument  json;
        QJsonArray     recordsArray;
        while(query.next())
        {
            QJsonObject recordObject;
            for(int x=0; x < query.record().count(); x++)
            {
                recordObject.insert( query.record().fieldName(x),QJsonValue::fromVariant(query.value(x)) );
            }
            recordsArray.push_back(recordObject);
        }
        json.setArray(recordsArray);
//        qDebug()<<json.toJson();
        return json;
    }
    else{
        qDebug()<<"未找到数据！";
        return  QJsonDocument();
    }
    query.clear();
    query.finish();
    this->db.close();
}

int SQLTOOL::InsertIntoTable(const QString &sql)
{
    QSqlQuery query;
    if (query.exec(sql))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool SQLTOOL::appendData(const QList<QString> &data,const QString &tablename)
{
    QSqlQuery query;
    try
    {
        this->db.transaction();

        QString sqlstring = QString("insert into %1 values(").arg(tablename);
        const int size = getNameFromTable(tablename).size();
        for (int i = 0; i < size; i++)
        {
            if (i != size - 1)
            {
                sqlstring += "?,";
            }
            else
            {
                sqlstring += "?";
            }
        }
        sqlstring += ")";
        qDebug() << sqlstring;
        query.prepare(sqlstring);
        QVariantList temp[1000];
        qDebug() << data.size();
        qDebug() << size;
        int cnt = 0;

        for (auto &itor : data)
        {
            qDebug() << itor;
            temp[cnt] << itor;
            cnt++;
            if (size != 0) {
                if ((cnt) % size == 0 )
                {
                    cnt = 0;
                }
            }
            else
            {
                cnt = 0;
            }
        }
        /*for (int i = 0; i < data.size(); i += size-1)
        {
            for (int j = 0; j < size; j++)
            {
                temp[j] << data.at(i*size+j);
                qDebug() << "i="<<i;
                qDebug() << "j="<<j;
                qDebug() << "position="<<i * size + j;

            }

        }*/

        for (int i = 0; i < size; i++)
        {
            qDebug() << temp[i];
            query.addBindValue(temp[i]);
        }

        query.execBatch();
        if (this->db.commit())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    catch (const std::exception&)
    {
        return false;
    }


}
int SQLTOOL::updateTable(const QString &tablename, const QString &colname, const QString &val, const QString &pk, const QString &pkval)
{
    QString sql = QString("update %1 SET %2 = \"%3\" where %4 = \"%5\";").arg(tablename,colname,val,pk,pkval);
    QSqlQuery query;
    query.prepare(sql);
    try
    {
        qDebug().noquote() << sql;
        if (query.exec()) {
            return true;
        }
        else
        {
            return false;
        }
    }
    catch (const std::exception&)
    {
        return false;
    }

}

int SQLTOOL::dataSizeoftable(const QString &name)
{
    QSqlQuery sql;

    QList<QString> result;
    try
    {
        sql.exec(QString("select * from %1").arg(name));

        while (sql.next())
        {
            result.append(sql.value(0).toString());
        }
    }
    catch (const std::exception&)
    {
        qDebug() << "false";
    }
    return result.size();
}

bool SQLTOOL::deletedata(const QString &name,QList<QString> header,QList<QString> para)
{
    QSqlQuery sql;
    sql.exec();
    QString empty = QString("delete from %1 where ").arg(name);
    for (int i = 0; i < para.size(); i++)
    {
        empty +=  header.at(i);
        empty += "=";
        empty += "\""+para.at(i)+"\"";
        if (i != para.size() - 1)
        {
            empty += "and ";
        }
    }
    qDebug() << empty;
    if (sql.exec(empty))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool SQLTOOL:: execbathInsert(const QList<QStringList> &para)
{
    QSqlQuery sql;

    this->db.transaction();
    sql.prepare(para.at(0).at(0));
    QVariantList s[100];
    /*qDebug() << para.at(0).at(0);
    qDebug() << para.at(0).at(1);
    qDebug() << para.at(1).count();
    qDebug() << para.at(1).size();
    qDebug() << para.at(0).at(1).toInt();*/

    for (int i = 0; i < para.at(1).count(); i++)
    {
        //qDebug() << para.at(1).at(i);
        s[i%para.at(0).at(1).toInt()] << para.at(1).at(i);

    }
    for (int i = 0; i < para.at(0).at(1).toInt(); i++)
    {
        //qDebug() << s[i];
        sql.addBindValue(s[i]);
    }

    if (!sql.execBatch())
    {
        //qDebug() << sql.lastError();
        return false;
    }
    this->db.commit();

    return true;
}
