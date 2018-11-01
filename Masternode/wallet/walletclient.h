#ifndef WALLETCLIENT_H
#define WALLETCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QDebug>
#include <QHostAddress>

#include "walletinfos.h"


class WalletClient : public QThread
{
    Q_OBJECT
public:
    explicit WalletClient(qintptr socketDescriptor, WalletInfos *walletinfos, QObject *parent = nullptr);
    void run();
signals:

public slots:

private slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *m_socket;
    qintptr m_socketDescriptor;
    void sendTCP(QString msg);
    WalletInfos *m_walletinfos;
};

#endif // WALLETCLIENT_H
