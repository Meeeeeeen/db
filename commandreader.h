#ifndef COMMANDREADER_H
#define COMMANDREADER_H

#include <QString>

class CommandReader {
public:
    CommandReader();
    QString readDatabaseFilePath();
    QString readUserQuery();
};

#endif // COMMANDREADER_H
