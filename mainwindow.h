#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>

class QHttpClient;

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
private slots:
    void onFinished(const QJsonDocument &response);
    void on_btnSend_clicked();

private:
    void init();
    bool setUrl();
    void setBody();

    Ui::MainWindow *ui;
    QHttpClient *m_http;
};

#endif // MAINWINDOW_H
