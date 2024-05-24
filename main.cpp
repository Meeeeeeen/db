#include <QCoreApplication>
#include <QFile>
#include <iostream>
#include <QtSql>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

bool checkDatabaseFile(const QString &filePath) {
    if (QFile::exists(filePath)) {
        std::cout << "Файл базы данных существует.\n";
        return true;
    } else {
        std::cout << "Файл базы данных не существует. Будет создан новый файл базы данных.\n";
        return false;
    }
}

QSqlDatabase connectToDatabase(const QString &filePath) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filePath);
    if (db.open()) {
        std::cout << "Подключение к базе данных успешно.\n";
    } else {
        std::cerr << "Не удалось подключиться к базе данных: " << db.lastError().text().toStdString() << "\n";
        exit(1);
    }
    return db;
}

void createTestTable(QSqlDatabase &db) {
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS test ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name TEXT NOT NULL,"
               "age INTEGER"
               ")");
    query.exec("INSERT INTO test (name, age) VALUES ('Иван', 25)");
    query.exec("INSERT INTO test (name, age) VALUES ('Мария', 30)");
    query.exec("INSERT INTO test (name, age) VALUES ('Петр', 40)");
    std::cout << "Тестовая таблица 'test' создана и заполнена данными.\n";
}

void disconnectFromDatabase(QSqlDatabase &db) {
    if (db.isOpen()) {
        db.close();
        std::cout << "Отключение от базы данных успешно.\n";
    }
}

void executeSQLQuery(QSqlDatabase &db, const QString &query) {
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

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    std::string dbFilePath;
    setlocale(LC_ALL, "ru_RU.UTF-8");

#ifdef _WIN32
    // Устанавливаем кодовую страницу консоли на UTF-8
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::cout << "Введите путь к файлу базы данных: ";
    std::getline(std::cin, dbFilePath);

    bool dbExists = checkDatabaseFile(QString::fromStdString(dbFilePath));

    QSqlDatabase db = connectToDatabase(QString::fromStdString(dbFilePath));

    // если бд только что создана - добавляем тестовую таблицу
    if (!dbExists) {
        createTestTable(db);
    }

    std::string userQuery;
    while (true) {
        std::cout << "Введите ваш SQL-запрос (или введите 'exit' для выхода): ";
        std::getline(std::cin, userQuery);
        if (userQuery == "exit") {
            break;
        }
        executeSQLQuery(db, QString::fromStdString(userQuery));
    }

    // отключаемся от базы данных перед выходом
    disconnectFromDatabase(db);

    return a.exec();
}
