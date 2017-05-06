#include "otpwidget.h"
#include "ui_otpwidget.h"

#include <ctime>

#include <oath.h>

#include <QDebug>

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
    QByteArray secret = m_secret.toUtf8();
    char **secretDecoded;
    size_t *secretLength;
    qDebug() << m_secret << m_secret.size();
    if (oath_base32_decode(secret.data(), m_secret.size(), secretDecoded, secretLength) != OATH_OK) {
        ui->codeLabel->setText("ERROR");
        return QString();
    }

    char totpCode[16];
    if (oath_totp_generate(*secretDecoded, *secretLength, std::time(0), 0, 0, 6, totpCode) == OATH_OK)
    {
        ui->codeLabel->setText(totpCode);
        return totpCode;
    }

    ui->codeLabel->setText("ERROR");
    return QString();
}

void OTPWidget::updateWidget()
{
    int epoch = std::time(0);
    int countDown = 30 - (epoch % 30);

    if (epoch % 30 == 29) {
        totpGenerate();
    }

    ui->timerBar->setValue(countDown);
    qDebug() << QString::number(countDown);
    //totpGenerate();
}
