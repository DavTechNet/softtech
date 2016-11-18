#ifndef EXPORT_H
#define EXPORT_H

#include <QObject>
#include <QFileDialog>
#include <QSqlRecord>
#include <QSqlField>
#include <QTextCodec>
#include "Database.h"

class Export : public QObject
{
    Q_OBJECT
public:
    explicit Export(QObject *parent = 0);
    //Export(QObject *parent = 0, QString separator, QString codec, QString directory);
    bool ToCsv();
    bool SoftToCsv(QSqlQueryModel *tableSoft);
    bool LoanToCsv(QSqlQueryModel *tableLoan);
    void setSeparator(QString separator);
    void setDirectory(QString directory);
    void setCodec (QString codec);

signals:
    
private:
    QString m_separator, m_codec, m_directory;

public slots:
    
};

#endif // EXPORT_H
