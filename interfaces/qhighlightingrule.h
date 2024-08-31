#ifndef QHIGHLIGHTINGRULE_H
#define QHIGHLIGHTINGRULE_H

#include <QRegularExpression>
#include <QTextCharFormat>

struct QHighlightingRule
{    
    QRegularExpression pattern;
    QTextCharFormat format;
};

#endif // QHIGHLIGHTINGRULE_H
