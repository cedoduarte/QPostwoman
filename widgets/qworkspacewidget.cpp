#include "qworkspacewidget.h"
#include "ui_qworkspacewidget.h"
#include "../services/qhttpclient.h"

#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QClipboard>
#include <QApplication>

QWorkspaceWidget::QWorkspaceWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QWorkspaceWidget)
{
    ui->setupUi(this);
    init();
}

QWorkspaceWidget::~QWorkspaceWidget()
{
    delete ui;
}

QWorkspace QWorkspaceWidget::toWorkspace() const
{
    QWorkspace workspace;
    workspace.setHttpMethodCurrentIndex(ui->httpMethodCombo->currentIndex());
    workspace.setBody(ui->txtBody->toPlainText());
    workspace.setResponse(ui->txtResponse->toPlainText());
    workspace.setUrl(ui->txtUrl->text());
    workspace.setHeaders(ui->tableHeaders->headers());
    return workspace;
}

void QWorkspaceWidget::fromWorkspace(const QWorkspace &workspace)
{
    ui->httpMethodCombo->setCurrentIndex(workspace.httpMethodCurrentIndex());
    ui->txtUrl->setText(workspace.url());
    ui->txtBody->setText(workspace.body());
    ui->txtResponse->setText(workspace.response());
    ui->tableHeaders->setHeaders(workspace.headers());
}

void QWorkspaceWidget::init()
{
    m_http = new QHttpClient(this);
    connect(m_http, &QHttpClient::finished, this, &QWorkspaceWidget::onFinished);
}

bool QWorkspaceWidget::setUrl()
{
    QString url = ui->txtUrl->text();
    if (url.isEmpty())
    {
        return false;
    }
    m_http->setUrl(url);
    return true;
}

void QWorkspaceWidget::setBody()
{
    QString body = ui->txtBody->toPlainText();
    m_http->setBody(QJsonDocument::fromJson(body.toLatin1()));
}

void QWorkspaceWidget::setHeaders()
{
    m_http->clearHeaders();
    for (const QHttpHeader &header : ui->tableHeaders->headers())
    {
        m_http->addHeader(header);
    }
}

void QWorkspaceWidget::on_btnSend_clicked()
{
    if (!setUrl())
    {
        QMessageBox::critical(this, "Error", "The url is empty");
        return;
    }
    setBody();
    setHeaders();
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
        case Patch:
            m_http->patch();
            break;
    }
}

void QWorkspaceWidget::onFinished(const QByteArray &response)
{
    QString textResponse;
    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(response, &parseError);
    if (parseError.error == QJsonParseError::NoError)
    {
        // JSON formatted response
        textResponse = QString::fromUtf8(document.toJson(QJsonDocument::Indented));
    }
    else
    {
        // Raw response
        textResponse = QString::fromUtf8(response);
    }
    ui->txtResponse->setText(textResponse);
}

void QWorkspaceWidget::on_btnAddHeader_clicked()
{
    ui->tableHeaders->insertRow(ui->tableHeaders->rowCount());
}

void QWorkspaceWidget::on_btnRemoveHeader_clicked()
{
    ui->tableHeaders->removeRow(ui->tableHeaders->currentRow());
}

void QWorkspaceWidget::on_btnCopyResponse_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString textToCopy = ui->txtResponse->toPlainText();
    clipboard->setText(textToCopy);
}

void QWorkspaceWidget::on_btnClearResponse_clicked()
{
    ui->txtResponse->clear();
}

void QWorkspaceWidget::on_btnPasteBody_clicked()
{
    ui->txtBody->paste();
}

