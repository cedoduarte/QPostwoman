#ifndef QCODEHIGHLIGHTER_H
#define QCODEHIGHLIGHTER_H

#include "../../interfaces/qhighlightingrule.h"

#include <QSyntaxHighlighter>
#include <QVector>

class QCodeHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit QCodeHighlighter(QTextDocument *parent = nullptr);
    virtual ~QCodeHighlighter();
protected:
    void highlightBlock(const QString &text) override;
private:
    void init();

    QVector<QHighlightingRule> highlightingRules;
};

#endif // QCODEHIGHLIGHTER_H
