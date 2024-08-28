#ifndef QHTTPHEADER_H
#define QHTTPHEADER_H

#include <QString>

class QHttpHeader
{
public:
    QHttpHeader();
    QHttpHeader(const QString &key, const QString &value);
    QHttpHeader(const QHttpHeader &other);
    void operator=(const QHttpHeader &other);
    bool operator==(const QHttpHeader &other);
    bool operator!=(const QHttpHeader &other);
    virtual ~QHttpHeader();
    void setKey(const QString &key);
    void setValue(const QString &value);
    QString key() const;
    QString value() const;
private:
    QString m_key;
    QString m_value;
};

#endif // QHTTPHEADER_H
