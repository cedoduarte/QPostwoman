#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "services/qhttpclient.h"

#include <QDebug>
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

void MainWindow::init()
{
    m_http = new QHttpClient(this);
    connect(m_http, &QHttpClient::finished, this, &MainWindow::onFinished);
}

void MainWindow::onFinished(const QJsonDocument &response)
{

}

bool MainWindow::setUrl()
{
    QString url = ui->txtUrl->text();
    if (url.isEmpty())
    {
        return false;
    }
    m_http->setUrl(url);
    return true;
}

void MainWindow::setBody()
{
    QString body = ui->txtBody->toPlainText();
    m_http->setBody(QJsonDocument::fromJson(body.toLatin1()));
}

void MainWindow::on_btnSend_clicked()
{
    if (!setUrl())
    {
        QMessageBox::critical(this, "Error", "The url is empty");
        return;
    }
    setBody();
    HttpMethod method = ui->httpMethodCombo->currentMethod();
    switch (method)
    {
        case Get:
            m_http->get();
            break;
        case Post:
            m_http->post();
            break;
        case Put:
            m_http->put();
            break;
        case Delete:
            m_http->deleteResource();
            break;
    }
}

