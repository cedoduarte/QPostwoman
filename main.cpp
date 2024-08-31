#include "mainwindow.h"
#include "persistence/qsqlitedatabase.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("fusion");
    app.setApplicationName("QPostwoman");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("DuarteCorporation");
    app.setOrganizationDomain("www.duartecorporation.com");
    QSqliteDatabase db;
    db.init();
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
