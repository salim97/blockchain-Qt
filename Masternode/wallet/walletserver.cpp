#include "walletserver.h"

#include <QTcpSocket>

WalletServer::WalletServer(WalletInfos *walletinfos,Blockchain *blockchain, QObject *parent) : QObject(parent)
{
    m_walletinfos = walletinfos ;
    m_blockchain = blockchain ;
    m_tcpServer = new QTcpServer(this) ;
    if(!m_tcpServer->listen(QHostAddress::Any, tcpPort))
        qDebug() <<"m_tcpServer : " + m_tcpServer->errorString() ;
    else
        qDebug() << "TCP 127.0.0.1: " +QString::number(tcpPort)+" LISTENING." ;

    connect(m_tcpServer, SIGNAL(newConnection()),
            this, SLOT(newConnectionTCP()), Qt::DirectConnection);
}

void WalletServer::newConnectionTCP()
{
    QTcpSocket* readSocket = m_tcpServer->nextPendingConnection();
    qDebug() << "new connection " << readSocket->peerAddress().toString() ;

    connect( readSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    //noy working ... why ... idon't know i will fix it later
    //    WalletClient *thread = new WalletClient(readSocket->socketDescriptor(), m_walletinfos) ;

//    connect(thread, SIGNAL(finished()),
//            thread,   SLOT(deleteLater()));


//    thread->start();


}

void WalletServer::readyRead()
{
    qDebug() << "void WalletServer::readyRead()";
    QTcpSocket* m_socket = qobject_cast<QTcpSocket*>(sender());
    while (m_socket->bytesAvailable())
    {
        QString row = m_socket->readAll();
        if(row.contains("username:"))
        {
            QStringList tmps = row.split(":") ;
            if(tmps.length() == 2 )
            {
                WalletInfo walletInfo;
                walletInfo.userName = tmps.at(1) ;
                walletInfo.active = true ;
                walletInfo.remoteAddress = m_socket->peerAddress().toString() ;
                m_walletinfos->addNextWalletInfo(walletInfo);

                m_socket->write("blockchain:"+m_blockchain->toString().toUtf8());
            }
        }
        if(row.contains("transaciton:"))
        {

        }
        if(row.contains("transaciton:"))
        {
            // TODO : ...
        }
    }
}

