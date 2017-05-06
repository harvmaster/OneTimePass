#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <adddialog.h>
#include <otpwidget.h>

#include <oath.h>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    oath_init();

    // Create timer that triggers the OTP Widgets to update every second
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateOTPWidgets()));
    m_timer->start(1000);
}

MainWindow::~MainWindow()
{
    oath_done();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    AddDialog *addDialog = new AddDialog;

    // If the user clicked okay
    if (addDialog->exec() == QDialog::Accepted) {
        OTPWidget *otpWidget = new OTPWidget(this);
        otpWidget->setService(addDialog->getService());
        otpWidget->setSecret(addDialog->getSecret());
        otpWidget->totpGenerate();
        ui->otpWidgetsLayout->addWidget(otpWidget);
    }

    return;
}

void MainWindow::updateOTPWidgets()
{
    foreach (OTPWidget *otpWidget, ui->centralWidget->findChildren<OTPWidget*>()) {
        otpWidget->updateWidget();
    }
}
