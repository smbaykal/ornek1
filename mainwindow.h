#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;

private slots:
    void pushButtonOnClick();
    void downloadFinished(QNetworkReply* reply);
    void updateProgress(qint64 bytesReceived, qint64 totalBytes);
};

#endif // MAINWINDOW_H
