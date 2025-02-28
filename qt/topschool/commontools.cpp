#include "commontools.h"
#include <QPixmap>
#include <QPainter>

CommonTools::CommonTools()
{

}

QPixmap CommonTools::getPixFromBase64(const QModelIndex &idx,int columnIndex)
{
    QModelIndex urlIndex=idx.model()->index(idx.row(),columnIndex);
    QByteArray jepgData=urlIndex.data().toByteArray();

    QPixmap pix;
    pix.loadFromData(QByteArray::fromBase64(jepgData));

    return pix;
}

QPixmap CommonTools::getPixFromLogo(const QModelIndex &idx,int columnIndex)
{
    QString str=idx.model()->index(idx.row(),columnIndex).data().toString();

    QPixmap pix_211=QPixmap(":/jpg/211.jpg");
    QPixmap pix_985=QPixmap(":/jpg/985.jpg");
    QPixmap pix_qjjh=QPixmap(":/jpg/qjjh.jpg");
    QPixmap pix_syl=QPixmap(":/jpg/syl.jpg");

    int count=0;
    bool bSyl=false; bool b985=false;bool b211=false;bool bQjjh=false;
    int totalWidth=0;int totalHeight=pix_211.height();
    if (str.contains("双一流"))
    {
        count++;
        totalWidth+=pix_syl.width();
        bSyl=true;
    }
    if (str.contains("985"))
    {
        count++;
        totalWidth+=pix_985.width();
        b985=true;
    }
    if (str.contains("211"))
    {
        count++;
        totalWidth+=pix_211.width();
        b211=true;
    }
    if (str.contains("强基计划"))
    {
        count++;
        totalWidth+=pix_qjjh.width();
        bQjjh=true;
    }
    if(count>0)
    {
        QPixmap total_pixmap(QSize(totalWidth , totalHeight));
        QPainter painter(&total_pixmap);
        painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
        int index=0;
        int indexWidth=0;
        if(bSyl)
        {
            painter.drawPixmap(QRect(indexWidth,0,pix_syl.width(),totalHeight),pix_syl);
            indexWidth+=pix_syl.width();
            index++;
        }
        if(b985)
        {
            painter.drawPixmap(QRect(indexWidth,0,pix_985.width(),totalHeight),pix_985);
            indexWidth+=pix_985.width();
            index++;
        }
        if(b211)
        {
            painter.drawPixmap(QRect(indexWidth,0,pix_211.width(),totalHeight),pix_211);
            indexWidth+=pix_211.width();
            index++;
        }
        if(bQjjh)
        {
            painter.drawPixmap(QRect(indexWidth,0,pix_qjjh.width(),totalHeight),pix_qjjh);
            indexWidth+=pix_qjjh.width();
            index++;
        }

        QPixmap scaled_pixmap=total_pixmap.scaled(totalWidth/8,totalHeight/8,Qt::KeepAspectRatio);
        QPainter painterScaled(&scaled_pixmap);
        painterScaled.drawPixmap(totalWidth/8,totalHeight/8,scaled_pixmap);

        return scaled_pixmap;
    }

    return QPixmap();
}
