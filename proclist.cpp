#include "proclist.h"
#include <dirent.h>
#include <string.h>
#include <QRegularExpression>
#include <QTimer>
procList::procList(QWidget* parent) : QListWidget(parent)
{
    updateProcess();
}

procList::procList()
{
}
void procList::updateProcess()
{
    DIR* proc =opendir("/proc");
    if(proc)
    {
        while(QListWidget::count() != 0)
        {
            QListWidgetItem* item = QListWidget::takeItem(0);
            delete(item);
        }
        dirent *entry;
        while(entry = readdir(proc))
        {
            if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name,"..") != 0)
            {
                QString entryName(entry->d_name);
                QRegularExpression re("^\\d+$");
                if(re.match(entryName).hasMatch())
                    addItem(entryName);
            }
        }
        closedir(proc);
    }

}
