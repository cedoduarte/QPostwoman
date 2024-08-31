#include "qcodetextedit.h"
#include "qcodehighlighter.h"

QCodeTextEdit::QCodeTextEdit(QWidget *parent)
{
    init();
}

QCodeTextEdit::~QCodeTextEdit()
{
}

void QCodeTextEdit::init()
{
    m_highlighter = new QCodeHighlighter(document());

    // Apply Visual Studio Code-like styling using stylesheets
    QString styleSheet = R"(
            QTextEdit {
                background-color: #1E1E1E;
                color: #D4D4D4;
                font-family: 'Consolas', 'Courier New', monospace;
                font-size: 14px;
                border: 1px solid #3C3C3C;
                padding: 5px;
            }
            QTextEdit:focus {
                border: 1px solid #007ACC;
            }
        )";
    setStyleSheet(styleSheet);
}
