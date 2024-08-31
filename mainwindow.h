#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_actionClose_triggered();
    void on_actionNew_workspace_triggered();
private:
    void init();
    void loadSettings();
    void saveSettings();
    void loadWorkspaces();
    void saveWorkspaces();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
