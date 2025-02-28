#include "customsqltablemodel.h"
#include <QPixmap>
#include <QIcon>
#include <QPainter>
#include "commontools.h"

CustomSqlTableModel::CustomSqlTableModel(QObject *parent)
    : QSqlQueryModel{parent}
{

}

QVariant CustomSqlTableModel::data(const QModelIndex &idx, int role) const
{
    QVariant value=QSqlQueryModel::data(idx,role);

    if(0==idx.column()&&Qt::DecorationRole==role)
    {
        return QIcon(CommonTools::getPixFromBase64(idx,9));//第9列数据，写死了
    }
    //学校性质的图标处理
    if(5==idx.column()&&Qt::DecorationRole==role)
    {
        return CommonTools::getPixFromLogo(idx,6);
    }
    //===============

    return value;
}
