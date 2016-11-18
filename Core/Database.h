#ifndef DATABASE_H
#define DATABASE_H

#include "DatabaseInfos.h"
#include <QStringList>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSortFilterProxyModel>
#include <QSqlRelationalTableModel>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = 0);
    
signals:
    
public slots:
    static QList<QSqlQueryModel *> ReadAllTables();
    static QSqlQueryModel *ReadTableSoft();
    static QSqlTableModel *RWTableSoft();
    static QSqlQueryModel *ReadTableLoan();
    static QSqlTableModel *RWTableLoan();
    static QSqlQueryModel *ReadTitleEditor();
    static QSqlQueryModel *ReadBorrower();
    static QSqlQueryModel *SearchTableSoft(QString search, QString textSearch);
    static QSqlQueryModel *SelectionSoft(QString title, QString editor);
    static QSqlQueryModel *SoftInLoan(int idSoft);
    static QSortFilterProxyModel *LoanInTime();
    static bool CreateSQLiteDB(QString fileName);
    static QSqlRelationalTableModel *HistoryLoan();
};

#endif // DATABASE_H
