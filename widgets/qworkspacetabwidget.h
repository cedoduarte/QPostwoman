#ifndef QWORKSPACETABWIDGET_H
#define QWORKSPACETABWIDGET_H

#include "../interfaces/qworkspace.h"

#include <QTabWidget>
#include <vector>

class QWorkspaceWidget;

class QWorkspaceTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit QWorkspaceTabWidget(QWidget *parent = nullptr);
    virtual ~QWorkspaceTabWidget();
    void appendNewWorkspace();
    void insertWorkspace(const QWorkspace &workspace);
    QWorkspaceWidget* currentWorkspace() const;
    QWorkspaceWidget* workspace(int index) const;
    std::vector<QWorkspace> workspaces() const;
private:
    void init();
};

#endif // QWORKSPACETABWIDGET_H
