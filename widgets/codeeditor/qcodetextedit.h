#ifndef QCODETEXTEDIT_H
#define QCODETEXTEDIT_H

#include <QTextEdit>

class QCodeHighlighter;

class QCodeTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit QCodeTextEdit(QWidget *parent = nullptr);
    virtual ~QCodeTextEdit();
private:
    void init();

    QCodeHighlighter *m_highlighter;
};

#endif // QCODETEXTEDIT_H
