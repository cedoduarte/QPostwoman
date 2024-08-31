#include "qsqlitedatabase.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QJsonDocument>

QSqliteDatabase::QSqliteDatabase()
{
}

QSqliteDatabase::~QSqliteDatabase()
{
}

void QSqliteDatabase::init()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("qpostwoman.sqlite");
    if (!db.open())
    {
        qDebug().noquote().nospace() << db.lastError().text();
        return;
    }
    createEntities();
}

void QSqliteDatabase::insertWorkspace(const QWorkspace &workspace)
{
    QSqlQuery query;
    query.prepare("INSERT INTO workspaces(json) VALUES (:json)");
    query.bindValue(":json", QString::fromUtf8(QJsonDocument::fromVariant(workspace.toVariant()).toJson(QJsonDocument::Compact)));
    query.exec();
}

std::vector<QWorkspace> QSqliteDatabase::workspaces()
{
    std::vector<QWorkspace> workspaceList;
    QSqlQuery query;
    query.exec("SELECT * FROM workspaces");
    while (query.next())
    {
        QString json = query.value(1).toString();
        QWorkspace workspace;
        workspace.fromVariant(QJsonDocument::fromJson(json.toUtf8()).toVariant());
        workspaceList.push_back(workspace);
    }
    return workspaceList;
}

void QSqliteDatabase::truncateWorkspaces()
{
    QSqlQuery query;
    query.exec("DELETE FROM workspaces");
    query.exec("VACUUM");
}

void QSqliteDatabase::createEntities()
{
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS workspaces(id INTEGER PRIMARY KEY AUTOINCREMENT, json TEXT)"))
    {
        qDebug().noquote().nospace() << query.lastError().text();
    }
}
