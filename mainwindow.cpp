#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);

    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(pushButtonOnClick()));
    /*connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(downloadFinished(QNetworkReply*)));*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushButtonOnClick()
{
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("http://10.10.1.1/MAC/random_mac_list.txt")));
    /*connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateProgress(qint64,qint64)));*/

    // Lambda functions... Replaces MainWindow::updateProgress and MainWindow::downloadFinished

    // lambda function parameters come from &QNetworkReply::downloadProgress signal
    connect(reply, &QNetworkReply::downloadProgress,
            [&] (qint64 bytesReceived, qint64 bytesTotal) {
        double percent = (bytesReceived / bytesTotal) * 100;
        this->ui->progressBar->setValue(percent);
        this->ui->label->setText("Bytes received: " + QString::number(bytesReceived) + "\n" +
                           "Total bytes: " + QString::number(bytesTotal));
    });

    // if capture list doesn't specified crashes in reply->readAll()
    QObject::connect(reply, &QNetworkReply::finished, [this, reply](){
        QByteArray result = reply->readAll();
        QString data = result.data();
        this->ui->comboBox->clear();
        this->ui->comboBox->addItems(data.split("\n"));
        reply->close();
        reply->deleteLater();
    });
}

void MainWindow::updateProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    double percent = (bytesReceived / bytesTotal) * 100;
    ui->progressBar->setValue(percent);
    ui->label->setText("Bytes received: " + QString::number(bytesReceived) + "\n" +
                       "Total bytes: " + QString::number(bytesTotal));
}

void MainWindow::downloadFinished(QNetworkReply* reply)
{
    QByteArray result = reply->readAll();
    QString data = result.data();
    ui->comboBox->clear();
    ui->comboBox->addItems(data.split("\n"));
}
