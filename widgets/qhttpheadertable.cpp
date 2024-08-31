#include "qhttpheadertable.h"

#include <QTableWidgetItem>

QHttpHeaderTable::QHttpHeaderTable(QWidget *parent)
    : QTableWidget(parent)
{
    init();
}

QHttpHeaderTable::~QHttpHeaderTable()
{
}

std::vector<QHttpHeader> QHttpHeaderTable::headers() const
{
    std::vector<QHttpHeader> headerList;
    for (int iRow = 0; iRow < rowCount(); iRow++)
    {
        QHttpHeader header;
        QTableWidgetItem *keyItem = item(iRow, 0);
        QTableWidgetItem *valueItem = item(iRow, 1);
        header.setKey(keyItem ? keyItem->text() : "");
        header.setValue(valueItem ? valueItem->text() : "");
        headerList.push_back(header);
    }
    return headerList;
}

void QHttpHeaderTable::setHeaders(const std::vector<QHttpHeader> &headers)
{
    setRowCount(0);
    for (const QHttpHeader &header : headers)
    {
        const int iRow = rowCount();
        insertRow(iRow);
        setItem(iRow, 0, new QTableWidgetItem(header.key()));
        setItem(iRow, 1, new QTableWidgetItem(header.value()));
    }
}

void QHttpHeaderTable::init()
{
    setColumnCount(2);
    setHorizontalHeaderLabels({"Key", "Value"});

    insertRow(0);
    insertRow(1);

    setItem(0, 0, new QTableWidgetItem("Authorization"));
    setItem(1, 0, new QTableWidgetItem("Content-Type"));
    setItem(1, 1, new QTableWidgetItem("application/json"));
}
