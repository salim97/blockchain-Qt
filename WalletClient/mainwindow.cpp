#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    m_socket = new QTcpSocket(this) ;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    userName = ui->lineEdit_userName->text() ;
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_pushButton_connecte_clicked()
{
    m_socket->connectToHost(ui->lineEdit_ip->text(), ui->spinBox_port->value());
    connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

}

void MainWindow::connected()
{
    qDebug() << "void MainWindow::connected()";
    ui->stackedWidget->setCurrentIndex(2);

    sendTCP("username:"+userName);

}

void MainWindow::readyRead()
{
    qDebug() << "void MainWindow::readyRead()";
    QString tmp ;
    while (m_socket->bytesAvailable())
    {
        QString row = m_socket->readAll();
        qDebug() << "void WalletClient::readyRead()";
         ui->textEdit_in_out->append("<= "+row+"\n");
        if(row == "username:")
            sendTCP("username:"+userName);
        if(row.contains("blockchain:"))
        {
            row = row.split("blockchain:")[1] ;
            blockchain.fromString(row) ;
            int userHas = 0 ;
            int userSpend = 0 ;
            for(int i = 0 ; i < blockchain.length() ; i++ )
            {
                if(userName == blockchain.at(i).getData().sender())
                    userSpend += blockchain.at(i).getData().amount();
                if(userName == blockchain.at(i).getData().reciepient())
                    userHas += blockchain.at(i).getData().amount();

            }
            userHas -= userSpend ;
            ui->label_available_coin->setText(QString::number(userHas)+" ASR");
        }
    }

}

void MainWindow::disconnected()
{
    qDebug() << "void MainWindow::disconnected()";
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::sendTCP(QString msg)
{
    qDebug() <<" sendTCP: " << msg ;
    m_socket->write(msg.toUtf8()) ;
    ui->textEdit_in_out->append("=> "+msg+"\n");
}

void MainWindow::on_pushButton_send_clicked()
{
    Transaction transaction(userName, ui->lineEdit_send_to->text(), ui->spinBox_amount->value());
    sendTCP("transaction:"+transaction.toString());
}
