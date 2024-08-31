#ifndef QWORKSPACE_H
#define QWORKSPACE_H

#include "qhttpheader.h"

#include <QVariant>
#include <QString>
#include <vector>

class QWorkspace
{
public:
    explicit QWorkspace();
    virtual ~QWorkspace();

    QVariant toVariant() const;
    void fromVariant(const QVariant &input);

    void setHttpMethodCurrentIndex(int index);
    int httpMethodCurrentIndex() const;

    void setUrl(const QString &url);
    QString url() const;

    void setHeaders(const std::vector<QHttpHeader> &headers);
    std::vector<QHttpHeader> headers() const;

    void setBody(const QString &body);
    QString body() const;

    void setResponse(const QString &response);
    QString response() const;
private:
    int m_httpMethodCurrentIndex;
    QString m_url;
    std::vector<QHttpHeader> m_headers;
    QString m_body;
    QString m_response;
};

#endif // QWORKSPACE_H
