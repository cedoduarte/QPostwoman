#include "qcodehighlighter.h"

QCodeHighlighter::QCodeHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    init();
}

QCodeHighlighter::~QCodeHighlighter()
{
}

void QCodeHighlighter::highlightBlock(const QString &text)
{
    for (const QHighlightingRule &rule : highlightingRules)
    {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}

void QCodeHighlighter::init()
{
    // Keyword format
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(QColor(0x569CD6));
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns = {
        "\\bnull\\b", "\\btrue\\b", "\\bfalse\\b"
    };
    for (const QString &pattern : keywordPatterns)
    {
        QHighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Class name format
    QTextCharFormat classFormat;
    classFormat.setForeground(QColor(0x4EC9B0));
    classFormat.setFontWeight(QFont::Bold);
    QHighlightingRule classRule;
    classRule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
    classRule.format = classFormat;
    highlightingRules.append(classRule);

    // Single-line comment format
    QTextCharFormat singleLineCommentFormat;
    singleLineCommentFormat.setForeground(QColor(0x6A9955));
    singleLineCommentFormat.setFontItalic(true);
    QHighlightingRule commentRule;
    commentRule.pattern = QRegularExpression("//[^\n]*");
    commentRule.format = singleLineCommentFormat;
    highlightingRules.append(commentRule);

    // Quotation format
    QTextCharFormat quotationFormat;
    quotationFormat.setForeground(QColor(0xCE9178));
    QHighlightingRule quotationRule;
    quotationRule.pattern = QRegularExpression("\".*\"");
    quotationRule.format = quotationFormat;
    highlightingRules.append(quotationRule);

    // Function format
    QTextCharFormat functionFormat;
    functionFormat.setForeground(QColor(0xDCDCAA));
    QHighlightingRule functionRule;
    functionRule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    functionRule.format = functionFormat;
    highlightingRules.append(functionRule);

    // Number format
    QTextCharFormat numberFormat;
    numberFormat.setForeground(QColor(0xB5CEA8));
    QHighlightingRule numberRule;
    numberRule.pattern = QRegularExpression("\\b\\d+\\.?\\d*\\b");
    numberRule.format = numberFormat;
    highlightingRules.append(numberRule);
}
