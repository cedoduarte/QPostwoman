#ifndef QHTTPHEADERTABLE_H
#define QHTTPHEADERTABLE_H

#include "../interfaces/qhttpheader.h"

#include <QTableWidget>
#include <vector>

class QHttpHeaderTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit QHttpHeaderTable(QWidget *parent = nullptr);
    virtual ~QHttpHeaderTable();
    std::vector<QHttpHeader> headers() const;
    void setHeaders(const std::vector<QHttpHeader> &headers);
private:
    void init();
};

#endif // QHTTPHEADERTABLE_H
