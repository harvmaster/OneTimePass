#include "otpwidget.h"
#include "ui_otpwidget.h"

#include <ctime>

#include <oath.h>

OTPWidget::OTPWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OTPWidget)
{
    ui->setupUi(this);
}

OTPWidget::~OTPWidget()
{
    delete ui;
}

void OTPWidget::setService(QString service)
{
    ui->serviceNameLabel->setText(service);
}

void OTPWidget::setSecret(QString secret)
{
    m_secret=secret;
}

QString OTPWidget::totpGenerate()
{
    char **secretDecoded;
    size_t *secretLength;
    oath_base32_decode(m_secret.toStdString().c_str(), m_secret.size(), secretDecoded, secretLength);

    char totpCode[12];

    if (oath_totp_generate(*secretDecoded, *secretLength, std::time(0), 0, 0, 6, totpCode) == OATH_OK)
    {
        ui->codeLabel->setText(totpCode);
        return totpCode;
        //
    }

    ui->codeLabel->setText("ERROR");
    return QString();
}
