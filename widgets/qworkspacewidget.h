#ifndef QWORKSPACEWIDGET_H
#define QWORKSPACEWIDGET_H

#include "../interfaces/qworkspace.h"

#include <QWidget>

class QHttpClient;

namespace Ui
{
class QWorkspaceWidget;
}

class QWorkspaceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QWorkspaceWidget(QWidget *parent = nullptr);
    virtual ~QWorkspaceWidget();
    QWorkspace toWorkspace() const;
    void fromWorkspace(const QWorkspace &workspace);
private slots:
    void onFinished(const QByteArray &response);
    void on_btnSend_clicked();
    void on_btnAddHeader_clicked();
    void on_btnRemoveHeader_clicked();
    void on_btnCopyResponse_clicked();
    void on_btnClearResponse_clicked();
    void on_btnPasteBody_clicked();
private:
    void init();
    bool setUrl();
    void setBody();
    void setHeaders();

    Ui::QWorkspaceWidget *ui;
    QHttpClient *m_http;
};

#endif // QWORKSPACEWIDGET_H
