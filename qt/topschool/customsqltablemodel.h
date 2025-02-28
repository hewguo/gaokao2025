#ifndef CUSTOMSQLTABLEMODEL_H
#define CUSTOMSQLTABLEMODEL_H

#include <QSqlQueryModel>

class CustomSqlTableModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit CustomSqlTableModel(QObject *parent = 0);
//    ~CustomSqlTableModel();

    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // CUSTOMSQLTABLEMODEL_H
