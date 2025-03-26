#ifndef SINGLECAPABILITY_H
#define SINGLECAPABILITY_H

#include <QTreeWidgetItem>

class singleCapability : public QTreeWidgetItem
{
public:
    singleCapability(QTreeWidgetItem* parent, int type);
    void setEnabled(bool);
    bool getEnabled() const;
private:
    bool m_enabled;
};

#endif // SINGLECAPABILITY_H
