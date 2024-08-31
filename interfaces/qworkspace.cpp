#include "qworkspace.h"

#include <QVariantMap>
#include <QVariantList>

QWorkspace::QWorkspace()
{
}

QWorkspace::~QWorkspace()
{
}

QVariant QWorkspace::toVariant() const
{
    QVariantMap map;
    map["httpMethodCurrentIndex"] = m_httpMethodCurrentIndex;
    map["url"] = m_url;

    QVariantList headers;
    for (const QHttpHeader &header : m_headers)
    {
        QVariantMap headerMap;
        headerMap[header.key()] = header.value();
        headers.append(headerMap);
    }
    map["headers"] = headers;

    map["body"] = m_body;
    map["response"] = m_response;
    return map;
}

void QWorkspace::fromVariant(const QVariant &input)
{
    QVariantMap map = input.toMap();
    m_httpMethodCurrentIndex = map["httpMethodCurrentIndex"].toInt();
    m_url = map["url"].toString();

    m_headers.clear();
    QVariantList headers = map["headers"].toList();
    for (const QVariant &header : headers)
    {
        QVariantMap headerMap = header.toMap();
        for (const QString &keyString : headerMap.keys())
        {
            QString valueString = headerMap[keyString].toString();
            m_headers.push_back(QHttpHeader(keyString, valueString));
        }
    }

    m_body = map["body"].toString();
    m_response = map["response"].toString();
}

void QWorkspace::setHttpMethodCurrentIndex(int index)
{
    m_httpMethodCurrentIndex = index;
}

int QWorkspace::httpMethodCurrentIndex() const
{
    return m_httpMethodCurrentIndex;
}

void QWorkspace::setUrl(const QString &url)
{
    m_url = url;
}

QString QWorkspace::url() const
{
    return m_url;
}

void QWorkspace::setHeaders(const std::vector<QHttpHeader> &headers)
{
    m_headers = headers;
}

std::vector<QHttpHeader> QWorkspace::headers() const
{
    return m_headers;
}

void QWorkspace::setBody(const QString &body)
{
    m_body = body;
}

QString QWorkspace::body() const
{
    return m_body;
}

void QWorkspace::setResponse(const QString &response)
{
    m_response = response;
}

QString QWorkspace::response() const
{
    return m_response;
}
