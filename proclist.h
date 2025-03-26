#ifndef PROCLIST_H
#define PROCLIST_H

#include <QListWidget>
#include <chrono>

class procList : public QListWidget
{
    Q_OBJECT
public:
    procList();
    procList(QWidget*);
public slots:
    void updateProcess();
};

#endif // PROCLIST_H
