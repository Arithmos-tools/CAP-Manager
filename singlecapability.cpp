#include "singlecapability.h"

singleCapability::singleCapability(QTreeWidgetItem* parent, int type) : QTreeWidgetItem(parent, type) {}


void singleCapability::setEnabled(bool enabled)
{
    m_enabled = enabled;
}
bool singleCapability::getEnabled() const
{
    return m_enabled;
}
