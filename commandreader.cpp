#include "commandreader.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

CommandReader::CommandReader() {
#ifdef _WIN32
    // Устанавливаем кодовую страницу консоли на UTF-8
    SetConsoleOutputCP(CP_UTF8);
#endif
    setlocale(LC_ALL, "ru_RU.UTF-8");
}

QString CommandReader::readDatabaseFilePath() {
    std::string dbFilePath;
    std::cout << "Введите путь к файлу базы данных: ";
    std::getline(std::cin, dbFilePath);
    return QString::fromStdString(dbFilePath);
}

QString CommandReader::readUserQuery() {
    std::string userQuery;
    std::cout << "Введите ваш SQL-запрос (или введите 'exit' для выхода): ";
    std::getline(std::cin, userQuery);
    return QString::fromStdString(userQuery).trimmed();
}
