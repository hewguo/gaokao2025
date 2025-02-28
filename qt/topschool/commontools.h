#ifndef COMMONTOOLS_H
#define COMMONTOOLS_H
#include <QModelIndex>

//公共函数
class CommonTools
{
public:
    CommonTools();

    static QPixmap getPixFromBase64(const QModelIndex &idx,int columnIndex);

    static QPixmap getPixFromLogo(const QModelIndex &idx,int columnIndex);
};

#endif // COMMONTOOLS_H
