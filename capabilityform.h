#ifndef CAPABILITYFORM_H
#define CAPABILITYFORM_H

#include <QMainWindow>
#include "singlecapability.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class capabilityform;
}
QT_END_NAMESPACE
class capabilityform : public QMainWindow
{
    Q_OBJECT
public:
    explicit capabilityform(QWidget *parent = nullptr, int type = 0, singleCapability* capability = nullptr);
    ~capabilityform();
public slots:
    void toggleEnabled(Qt::CheckState);
signals:

private:
    Ui::capabilityform *ui;
    singleCapability* m_capability;
};

#endif // CAPABILITYFORM_H
