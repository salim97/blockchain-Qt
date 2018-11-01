#ifndef WALLETSERVER_H
#define WALLETSERVER_H

#include <QObject>
#include <QTcpServer>
#include <blockchain.h>

#include "walletinfos.h"
#include "walletclient.h"

class WalletServer : public QObject
{
    Q_OBJECT
public:
    explicit WalletServer(WalletInfos *walletinfos, Blockchain *blockchain, QObject *parent = nullptr);

signals:

public slots:

private slots:
    void newConnectionTCP();
    void readyRead();
private:
    int tcpPort = 8564 ;
    QTcpServer *m_tcpServer = nullptr;
    WalletInfos *m_walletinfos;
    Blockchain *m_blockchain;
};

#endif // WALLETSERVER_H
