#include "qhttpclient.h"

#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslConfiguration>

QHttpClient::QHttpClient(QObject *parent)
    : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &QHttpClient::onFinished);
}

QHttpClient::~QHttpClient()
{
}

void QHttpClient::setUrl(const QString &url)
{
    m_url = url;
}

QString QHttpClient::url() const
{
    return m_url;
}

void QHttpClient::setBody(const QJsonDocument &body)
{
    m_body = body;
}

QJsonDocument QHttpClient::body() const
{
    return m_body;
}

std::vector<QHttpHeader> QHttpClient::headers() const
{
    return m_headers;
}

void QHttpClient::addHeader(const QHttpHeader &header)
{
    if (header.key().isEmpty() || header.value().isEmpty())
    {
        return;
    }
    m_headers.push_back(header);
}

void QHttpClient::clearHeaders()
{
    m_headers.clear();
}

void QHttpClient::removeHeader(const QString &key)
{
    int index = -1;
    for (int i = 0; i < int(m_headers.size()); i++)
    {
        if (m_headers[i].key() == key)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        std::vector<QHttpHeader>::iterator it = m_headers.begin();
        std::advance(it, index);
        m_headers.erase(it);
    }
}

void QHttpClient::get()
{
    m_httpMethod = "GET";
    m_manager->get(makeRequest());
}

void QHttpClient::post()
{
    m_httpMethod = "POST";
    m_manager->post(makeRequest(), m_body.toJson(QJsonDocument::Compact));
}

void QHttpClient::put()
{
    m_httpMethod = "PUT";
    m_manager->put(makeRequest(), m_body.toJson(QJsonDocument::Compact));
}

void QHttpClient::deleteResource()
{
    m_httpMethod = "DELETE";
    m_manager->deleteResource(makeRequest());
}

void QHttpClient::patch()
{
    m_httpMethod = "PATCH";
    m_manager->sendCustomRequest(makeRequest(), "PATCH", m_body.toJson(QJsonDocument::Compact));
}

void QHttpClient::onFinished(QNetworkReply *reply)
{
    QByteArray response;
    if (reply->error() != QNetworkReply::NoError)
    {
        response = QString(reply->errorString()).toLatin1();
    }
    else
    {
        response = reply->readAll();
    }
    emit finished(response);
    reply->deleteLater();
}

void QHttpClient::setHeaders(QNetworkRequest *request) const
{
    for (const QHttpHeader &header : m_headers)
    {
        request->setRawHeader(header.key().toLatin1(), header.value().toLatin1());
    }
}

QNetworkRequest QHttpClient::makeRequest() const
{
    QNetworkRequest request;
    request.setUrl(QUrl(m_url));
    QSslConfiguration sslConfig = request.sslConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(sslConfig);
    setHeaders(&request);
    return request;
}
