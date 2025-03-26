#include "capabilityform.h"
#include "./ui_capabilityform.h"
#include "capabilitiestree.h"
#include "capabilitiesArray.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>
capabilityform::capabilityform(QWidget *parent, int type, singleCapability* capability)
    : QMainWindow(parent)
    , ui(new Ui::capabilityform)
{
    m_capability = capability;
    ui->setupUi(this);
    connect(ui->isEnabled, &QCheckBox::checkStateChanged, this, &capabilityform::toggleEnabled);
    connect(ui->cancel, &QPushButton::clicked, this, &capabilityform::deleteLater);
    connect(ui->ok, &QPushButton::clicked, reinterpret_cast<capabilitiesTree*>(parent), &capabilitiesTree::updateCapabilities);
    setWindowTitle(QString(capindexToName[type]));
    ui->capName->setText(QString(capindexToName[type]));
    if(m_capability)
        ui->isEnabled->setCheckState(m_capability->getEnabled() ? Qt::Checked : Qt::Unchecked);
    QFile explanationFile(QString("cap_explanation.xml"));
    if(explanationFile.open(QIODeviceBase::ReadOnly, QFileDevice::ReadOwner))
    {
        QXmlStreamReader xmlResult(&explanationFile);
        while(!xmlResult.atEnd())
        {
            xmlResult.readNext();
            if(xmlResult.isStartElement())
            {
                if(xmlResult.name().toString() == QString("_")+QString::number(type))
                    ui->explanation->setText(xmlResult.readElementText());
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "file error !", "Unable to load the explanation file");
    }

}
void capabilityform::toggleEnabled(Qt::CheckState state)
{
    m_capability->setEnabled(state == Qt::Checked ? true : false);
}
capabilityform::~capabilityform()
{
    delete ui;
}
