#include "qhttpheadertable.h"

QHttpHeaderTable::QHttpHeaderTable(QWidget *parent)
    : QTableWidget(parent)
{
    init();
}

QHttpHeaderTable::~QHttpHeaderTable()
{
}

void QHttpHeaderTable::init()
{
    setColumnCount(2);
    setHorizontalHeaderLabels({"Key", "Value"});
}
