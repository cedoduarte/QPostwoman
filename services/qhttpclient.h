#ifndef QHTTPCLIENT_H
#define QHTTPCLIENT_H

#include "../interfaces/qhttpheader.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QJsonDocument>

class QHttpClient : public QObject
{
    Q_OBJECT
public:
    explicit QHttpClient(QObject *parent = nullptr);
    virtual ~QHttpClient();
    void setUrl(const QString &url);
    QString url() const;
    void setBody(const QJsonDocument &body);
    QJsonDocument body() const;
    std::vector<QHttpHeader> headers() const;
    void addHeader(const QHttpHeader &header);
    void clearHeaders();
    void removeHeader(const QString &key);
    void get();
    void post();
    void put();
    void deleteResource();
signals:
    void finished(const QJsonDocument &response);
private slots:
    void onFinished(QNetworkReply *reply);
private:
    void setHeaders(QNetworkRequest *request) const;
    QNetworkRequest makeRequest() const;

    QString m_url;
    QJsonDocument m_body;
    QNetworkAccessManager *m_manager;
    std::vector<QHttpHeader> m_headers;
};

#endif // QHTTPCLIENT_H
