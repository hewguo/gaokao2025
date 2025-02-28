#include "commondelegate.h"
#include <QPainter>
CommonDelegate::CommonDelegate()
{
}

//CommonDelegate::connect(){}
void CommonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem itemOption(option);
    if(itemOption.state&QStyle::State_HasFocus)
    {
        itemOption.state=itemOption.state^QStyle::State_HasFocus;
    }
    if(0==index.column())
    {
        QModelIndex urlIndex=index.model()->index(index.row(),9);
//        qDebug()<<urlIndex.data().toString();
        QByteArray jepgData=urlIndex.data().toByteArray();

        //===========================
        QPixmap pix;
        pix.loadFromData(QByteArray::fromBase64(jepgData));

        QRect rect=option.rect;
        rect.adjust(0,6,0,0);
        rect.setSize(QSize(20,20));
        pix.scaled(20,20,Qt::KeepAspectRatio);
        painter->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
        painter->drawPixmap(rect,pix);
    }
    if(5==index.column())
    {
        QString str=index.data().toString();
        int x=0;
        if (str.contains("双一流"))
        {
            QPixmap pix= QPixmap(":/png/syl.png");
            QRect rect=option.rect;
            rect.adjust(x,6,0,0);
            rect.setSize(QSize(60,20));
            pix.scaled(60,20,Qt::KeepAspectRatio);
            painter->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
            painter->drawPixmap(rect,pix);
            x+=60;
        }
        if (str.contains("985"))
        {
            QPixmap pix= QPixmap(":/png/985.png");
            QRect rect=option.rect;
            rect.adjust(x,6,0,0);
            rect.setSize(QSize(60,20));
            pix.scaled(60,20,Qt::KeepAspectRatio);
            painter->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
            painter->drawPixmap(rect,pix);
            x+=60;
        }
        if (str.contains("211"))
        {
            QPixmap pix= QPixmap(":/png/211.png");
            QRect rect=option.rect;
            rect.adjust(x,6,0,0);
            rect.setSize(QSize(60,20));
            pix.scaled(60,20,Qt::KeepAspectRatio);
            painter->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
            painter->drawPixmap(rect,pix);
            x+=60;
        }
        if (str.contains("强基计划"))
        {
            QPixmap pix= QPixmap(":/png/qjjh.png");
            QRect rect=option.rect;
            rect.adjust(x,6,0,0);
            rect.setSize(QSize(60,20));
            pix.scaled(60,20,Qt::KeepAspectRatio);
            painter->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
            painter->drawPixmap(rect,pix);
            x+=60;
        }

    }
    QStyledItemDelegate::paint(painter,itemOption,index);
}
