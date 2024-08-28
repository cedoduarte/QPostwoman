#include "qhttpmethodcombo.h"

QHttpMethodCombo::QHttpMethodCombo(QWidget *parent)
    : QComboBox(parent)
{
    init();
}

QHttpMethodCombo::~QHttpMethodCombo()
{
}

HttpMethod QHttpMethodCombo::currentMethod() const
{
    return HttpMethod(currentIndex());
}

void QHttpMethodCombo::init()
{
    addItems({"GET","POST","PUT","DELETE"});
}
