#include "walletclient.h"

WalletClient::WalletClient(qintptr socketDescriptor, WalletInfos *walletinfos, QObject *parent) : QThread(parent)
{
    this->m_socketDescriptor = socketDescriptor;
    m_walletinfos = walletinfos;
}

void WalletClient::run()
{
    qDebug() << "void WalletClient::run()";
    m_socket = new QTcpSocket();
    if(!m_socket->setSocketDescriptor(m_socketDescriptor))
    {
        // something's wrong, we just emit a signal
        qDebug() << m_socket->error();
        return;
    }
    else
    {
        qDebug() << "done " ;
    }

    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(readyRead()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(disconnected()),
            this, SLOT(disconnected()), Qt::DirectConnection);

    //sendTCP("username:") ;

}

void WalletClient::readyRead()
{
    qDebug() << "void WalletClient::readyRead()";
    QString tmp ;
    while (m_socket->bytesAvailable())
    {
        QString row = m_socket->readAll();
        qDebug() << "void WalletClient::readyRead()";
        qDebug() << " <= " << row;
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

            }
        }
        if(row.contains("transaciton:"))
        {
            // TODO : ...
        }
    }
}

void WalletClient::disconnected()
{
    qDebug() << m_socketDescriptor << " Disconnected";
    m_socket->deleteLater();
    exit(0);
}

void WalletClient::sendTCP(QString msg)
{
    //    qDebug() << m_socketDescriptor <<" sendTCP: " << msg ;
    m_socket->write(msg.toUtf8()) ;
}
