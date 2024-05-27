#ifndef DBHELPER_H
#define DBHELPER_H

#include <QtSql>
#include <QString>

class DbHelper {
public:
    explicit DbHelper(const QString &filePath);
    ~DbHelper();
    void createTestTable();
    void executeSQLQuery(const QString &query);

private:
    QSqlDatabase db;
};

#endif // DBHELPER_H
