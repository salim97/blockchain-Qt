#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

#include "blockchain.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void sendTCP(QString msg);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_connecte_clicked();

    void connected();
    void readyRead();
    void disconnected();
    void on_pushButton_send_clicked();

private:
    Ui::MainWindow *ui;
    QString userName ;
    QTcpSocket *m_socket ;
    Blockchain blockchain;
};

#endif // MAINWINDOW_H
