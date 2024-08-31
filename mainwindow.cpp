#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "persistence/qsqlitedatabase.h"

#include <QSettings>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    saveWorkspaces();
    QMainWindow::closeEvent(event);
}

void MainWindow::loadSettings()
{
    QSettings settings;
    settings.beginGroup("settings");
    if (settings.contains("geometry"))
    {
        QRect geometryRect = settings.value("geometry").value<QRect>();
        setGeometry(geometryRect);
    }
    settings.endGroup();
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.beginGroup("settings");
    settings.setValue("geometry", geometry());
    settings.endGroup();
}

void MainWindow::loadWorkspaces()
{
    QSqliteDatabase db;
    for (const QWorkspace &workspace : db.workspaces())
    {
        ui->tabWidget->insertWorkspace(workspace);
    }
}

void MainWindow::saveWorkspaces()
{
    QSqliteDatabase db;
    db.truncateWorkspaces();
    for (const QWorkspace &workspace : ui->tabWidget->workspaces())
    {
        db.insertWorkspace(workspace);
    }
}

void MainWindow::init()
{
    loadSettings();
    loadWorkspaces();
    if (ui->tabWidget->count() == 0)
    {
        ui->tabWidget->appendNewWorkspace();
    }
}

void MainWindow::on_actionClose_triggered()
{
    if (QMessageBox::question(this, "Exit", "Are you sure to exit?") == QMessageBox::Yes)
    {
        close();
    }
}

void MainWindow::on_actionNew_workspace_triggered()
{
    ui->tabWidget->appendNewWorkspace();
}

