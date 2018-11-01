#ifndef MINER_H
#define MINER_H

#include "blockchain.h"

#include <QCryptographicHash>
#include <QByteArray>
#include <QDateTime>
#include <QObject>
#include <qDebug>


class Miner : public QObject
{
    Q_OBJECT
public:
    explicit Miner(Blockchain *blockchain, QObject *parent = nullptr);


    bool validateNextBlock(const int index, const QByteArray prevHash, const QByteArray nextHash, const QDateTime timestamp);
    void generateNextBlock(Transaction transaction);
    int setGenesisBlock();


    Blockchain *blockchain() const;
    void loadBlockchain(QString blockchain);
signals:
    void updateTable() ;

private:
    Blockchain *m_blockchain;
};

#endif // MINER_H
