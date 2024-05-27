#include <QCoreApplication>
#include "dbhelper.h"
#include "commandreader.h"
#include <QFile>
#include <iostream>

bool checkDatabaseFile(const QString &filePath) {
    if (QFile::exists(filePath)) {
        std::cout << "Файл базы данных существует.\n";
        return true;
    } else {
        std::cout << "Файл базы данных не существует. Будет создан новый файл базы данных.\n";
        return false;
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    CommandReader commandReader;
    QString dbFilePath = commandReader.readDatabaseFilePath();

    bool dbExists = checkDatabaseFile(dbFilePath);

    {
        DbHelper dbHelper(dbFilePath);

        if (!dbExists) {
            dbHelper.createTestTable();
        }

        while (true) {
            QString userQuery = commandReader.readUserQuery();
            if (userQuery.toLower() == "exit") {  // Приведение к нижнему регистру для сравнения
                break;
            }
            dbHelper.executeSQLQuery(userQuery);
        }
    }  // dbHelper выходит из области видимости и его деструктор вызывается здесь

    return a.exec();
}
