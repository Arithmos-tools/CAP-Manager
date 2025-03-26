#ifndef CAPABILITIESTREE_H
#define CAPABILITIESTREE_H

#include <QTreeWidget>
#include <QListWidgetItem>

class capabilitiesTree : public QTreeWidget
{
public:
    capabilitiesTree();
    capabilitiesTree(QWidget*);
public slots:
    void updateTree(QListWidgetItem*);
    void openInfo(QTreeWidgetItem*, int);
    void updateCapabilities();
private:
    int m_pid;
};


#endif // CAPABILITIESTREE_H
