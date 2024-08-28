#include "qhttpheader.h"

QHttpHeader::QHttpHeader()
{
    m_key = "";
    m_value = "";
}

QHttpHeader::QHttpHeader(const QString &key, const QString &value)
{
    m_key = key;
    m_value = value;
}

QHttpHeader::QHttpHeader(const QHttpHeader &other)
{
    m_key = other.m_key;
    m_value = other.m_value;
}

void QHttpHeader::operator=(const QHttpHeader &other)
{
    m_key = other.m_key;
    m_value = other.m_value;
}

bool QHttpHeader::operator==(const QHttpHeader &other)
{
    return m_key == other.m_key && m_value == other.m_value;
}

bool QHttpHeader::operator!=(const QHttpHeader &other)
{
    return !(*this == other);
}

QHttpHeader::~QHttpHeader()
{
}

void QHttpHeader::setKey(const QString &key)
{
    m_key = key;
}

void QHttpHeader::setValue(const QString &value)
{
    m_value = value;
}

QString QHttpHeader::key() const
{
    return m_key;
}

QString QHttpHeader::value() const
{
    return m_value;
}
