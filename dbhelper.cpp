#include "dbhelper.h"
#include <iostream>

DbHelper::DbHelper(const QString &filePath) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filePath);
    if (db.open()) {
        std::cout << "Подключение к базе данных успешно.\n";
    } else {
        std::cerr << "Не удалось подключиться к базе данных: " << db.lastError().text().toStdString() << "\n";
        exit(1);
    }
}

DbHelper::~DbHelper() {
    if (db.isOpen()) {
        db.close();
        std::cout << "Отключение от базы данных успешно.\n";
    }
}

void DbHelper::createTestTable() {
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS test ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name TEXT NOT NULL,"
               "birthdate TEXT"
               ")");
    query.exec("INSERT INTO test (name, birthdate) VALUES ('Иван', '1998-03-25')");
    query.exec("INSERT INTO test (name, birthdate) VALUES ('Мария', '1993-06-15')");
    query.exec("INSERT INTO test (name, birthdate) VALUES ('Петр', '1983-11-22')");
    std::cout << "Тестовая таблица 'test' создана и заполнена данными.\n";
}

void DbHelper::executeSQLQuery(const QString &query) {
    QSqlQuery qry(db);
    if (qry.exec(query)) {
        std::cout << "Запрос выполнен успешно.\n";
        while (qry.next()) {
            for (int i = 0; i < qry.record().count(); ++i) {
                std::cout << qry.value(i).toString().toStdString() << "\t";
            }
            std::cout << "\n";
        }
    } else {
        std::cerr << "Не удалось выполнить запрос: " << qry.lastError().text().toStdString() << "\n";
    }
}
