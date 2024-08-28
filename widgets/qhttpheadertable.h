#ifndef QHTTPHEADERTABLE_H
#define QHTTPHEADERTABLE_H

#include <QTableWidget>

class QHttpHeaderTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit QHttpHeaderTable(QWidget *parent = nullptr);
    virtual ~QHttpHeaderTable();
private:
    void init();
};

#endif // QHTTPHEADERTABLE_H
