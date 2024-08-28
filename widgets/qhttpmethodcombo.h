#ifndef QHTTPMETHODCOMBO_H
#define QHTTPMETHODCOMBO_H

#include "../enums/enums.h"

#include <QComboBox>

class QHttpMethodCombo : public QComboBox
{
    Q_OBJECT
public:
    explicit QHttpMethodCombo(QWidget *parent = nullptr);
    virtual ~QHttpMethodCombo();
    HttpMethod currentMethod() const;
private:
    void init();
};

#endif // QHTTPMETHODCOMBO_H
