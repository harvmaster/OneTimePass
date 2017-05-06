#ifndef OTPWIDGET_H
#define OTPWIDGET_H

#include <QWidget>

namespace Ui {
class OTPWidget;
}

class OTPWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OTPWidget(QWidget *parent = 0);
    ~OTPWidget();

    void setService(QString service);
    void setSecret(QString secret);

    QString totpGenerate();

    void updateWidget();

private:
    Ui::OTPWidget *ui;

    QString m_secret;
};

#endif // OTPWIDGET_H
