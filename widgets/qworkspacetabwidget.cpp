#include "qworkspacetabwidget.h"
#include "qworkspacewidget.h"

#include <QIcon>

QWorkspaceTabWidget::QWorkspaceTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    init();
}

QWorkspaceTabWidget::~QWorkspaceTabWidget()
{
}

void QWorkspaceTabWidget::appendNewWorkspace()
{
    addTab(new QWorkspaceWidget(this), QIcon(":/img/workspace.png"), "Workspace");
}

void QWorkspaceTabWidget::insertWorkspace(const QWorkspace &workspace)
{
    QWorkspaceWidget *workspaceWidget = new QWorkspaceWidget(this);
    workspaceWidget->fromWorkspace(workspace);
    addTab(workspaceWidget, QIcon(":/img/workspace.png"), "Workspace");
}

QWorkspaceWidget *QWorkspaceTabWidget::currentWorkspace() const
{
    QWorkspaceWidget *workspaceWidget = dynamic_cast<QWorkspaceWidget*>(currentWidget());
    return workspaceWidget;
}

QWorkspaceWidget *QWorkspaceTabWidget::workspace(int index) const
{
    QWorkspaceWidget *workspaceWidget = dynamic_cast<QWorkspaceWidget*>(widget(index));
    return workspaceWidget;
}

std::vector<QWorkspace> QWorkspaceTabWidget::workspaces() const
{
    std::vector<QWorkspace> workspaceList;
    for (int iWorkspace = 0; iWorkspace < count(); iWorkspace++)
    {
        workspaceList.push_back(workspace(iWorkspace)->toWorkspace());
    }
    return workspaceList;
}

void QWorkspaceTabWidget::init()
{
    setTabsClosable(true);
    connect(this, &QWorkspaceTabWidget::tabCloseRequested, this, [&](int index)
    {
        widget(index)->deleteLater();
        removeTab(index);
    });
}
