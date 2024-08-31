#ifndef QSQLITEDATABASE_H
#define QSQLITEDATABASE_H

#include "../interfaces/qworkspace.h"

#include <vector>

class QSqliteDatabase
{
public:
    explicit QSqliteDatabase();
    virtual ~QSqliteDatabase();
    void init();
    void insertWorkspace(const QWorkspace &workspace);
    std::vector<QWorkspace> workspaces();
    void truncateWorkspaces();
private:
    void createEntities();
};

#endif // QSQLITEDATABASE_H
