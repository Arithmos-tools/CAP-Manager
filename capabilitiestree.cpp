#include "capabilitiestree.h"
#include "/usr/include/linux/capability.h"
#include <sys/syscall.h>
#include <unistd.h>
#include <QMessageBox>
#include "capabilityform.h"
#include "capabilitiesArray.h"
#include "singlecapability.h"
capabilitiesTree::capabilitiesTree() {




}
capabilitiesTree::capabilitiesTree(QWidget *parent) : QTreeWidget(parent)
{
    for(int i = 0; i < 3; ++i)
    {
        QTreeWidgetItem *item  = new QTreeWidgetItem(this);
        item->setText(0, QString(capType[i]));
        QTreeWidgetItem *child  = new QTreeWidgetItem(item);
        child->setText(0, QString("Value[0] : N/A"));
        QTreeWidgetItem *child2  = new QTreeWidgetItem(item);
        child2->setText(0, QString("Value[1] : N/A"));
        for(int j = 0; j < sizeofcapindexToName; ++j)
        {
            singleCapability *capChild  = new singleCapability(item, 1000+j);
            capChild->setText(0, QString(QString(capindexToName[j])+ QString(" (") + QString::number(j) + QString(") : N/A")));
        }
    }
}

void capabilitiesTree::updateTree(QListWidgetItem *item)
{
    QTreeWidget::setHeaderLabel(item->text());
    __user_cap_header_struct userCapRequest;
    __user_cap_data_struct userCapResult[2];
    userCapRequest.version = _LINUX_CAPABILITY_VERSION_3;
    userCapRequest.pid = QString(item->text()).toInt();
    m_pid = userCapRequest.pid;
    int ret = syscall(SYS_capget, &userCapRequest, &userCapResult);
    if(ret == 0)
    {
        __u32* resultsSet[2][3] = {{&userCapResult[0].effective, &userCapResult[0].permitted, &userCapResult[0].inheritable},&userCapResult[1].effective, &userCapResult[1].permitted, &userCapResult[1].inheritable};
        for(int i = 0; i < 3; ++i)
        {
            QList<QTreeWidgetItem*> capCategory = findItems(capType[i], Qt::MatchExactly);
            if(capCategory.size() != 0)
            {
                if((*capCategory.begin())->child(0) && (*capCategory.begin())->child(1))
                {
                    for(int j = 0;j < 2; ++j)
                        (*capCategory.begin())->child(j)->setText(0,QString("Value[") + QString::number(j) +QString("] : ") + QString::number(*resultsSet[j][i]));
                }
                for(int k = 0; k < sizeofcapindexToName; ++k)
                {
                    singleCapability *capChild = reinterpret_cast<singleCapability*>((*capCategory.begin())->child(k+2));
                    if(capChild)
                    {
                        bool isEnabled = (k > 31 ? (*resultsSet[1][i] & (unsigned int)std::pow(2, k-32)) != 0 : (*resultsSet[0][i] & (unsigned int)std::pow(2, k)) != 0);
                        capChild->setText(0, QString(QString(capindexToName[k])+ QString(" (") + QString::number(k) + (isEnabled ?  QString(") : Enabled") : QString(") : Disabled") )));
                        capChild->setEnabled(isEnabled);
                    }
                }

            }
        }
    }
    else
    {
        QMessageBox::warning(this, "kernel error !", "Error while getcap, try to refresh the process list");
    }

}

 void capabilitiesTree::openInfo(QTreeWidgetItem* item, int column)
{
     if(item->type() >999)
    {
        singleCapability *capChild = reinterpret_cast<singleCapability*>(item);
        capabilityform *w = new capabilityform(this, item->type()-1000, capChild);

        w->show();
    }

}

void capabilitiesTree::updateCapabilities()
{
    __user_cap_header_struct userCapRequest;
    __user_cap_data_struct userCapResult[2];
    userCapRequest.version = _LINUX_CAPABILITY_VERSION_3;
    userCapRequest.pid = m_pid;
    __u32* resultsSet[2][3] = {{&userCapResult[0].effective, &userCapResult[0].permitted, &userCapResult[0].inheritable},&userCapResult[1].effective, &userCapResult[1].permitted, &userCapResult[1].inheritable};
    memset(userCapResult, 0, sizeof(__u32)* 6);
    for(int i = 0; i < 3; ++i)
    {
        QList<QTreeWidgetItem*> capCategory = findItems(capType[i], Qt::MatchExactly);
        if(capCategory.size() != 0)
        {
            for(int k = 0; k < sizeofcapindexToName; ++k)
            {
                singleCapability *capChild = reinterpret_cast<singleCapability*>((*capCategory.begin())->child(k+2));
                if(capChild)
                {
                    *(resultsSet[k >31 ? 1 : 0][i]) = (*(resultsSet[k >31 ? 1 : 0][i]) | (capChild->getEnabled() ? ((k > 31) ? ((__u32)std::pow(2, k-31)) : ((__u32)std::pow(2, k))): 0));
                }
            }
        }
    }
    int ret = syscall(SYS_capset, &userCapRequest, &userCapResult);
    if(ret != 0)
        QMessageBox::warning(this, "kernel error !", "Unable to call capset, return value : " + QString::number(ret) + QString(" errno : ") + QString::number(errno));
}
