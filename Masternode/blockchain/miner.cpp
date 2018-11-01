#include "miner.h"

Miner::Miner(Blockchain *blockchain, QObject *parent) : QObject(parent)
{
    m_blockchain = blockchain;
}



bool Miner::validateNextBlock(const int index, const QByteArray prevHash, const QByteArray nextHash, const QDateTime timestamp)
{
    // TODO : add more condition...
    bool isValid = true;
    if(index != m_blockchain->getLastBlockIndex() + 1){
        isValid = false;
    }
    if(prevHash != m_blockchain->getLastBlockHash()){
        isValid = false;
    }

    if(m_blockchain->getLastBlockTimestamp() >= timestamp || timestamp >= QDateTime::currentDateTime()){
        isValid = false;
    }
    return isValid;
}

void Miner::generateNextBlock(Transaction transaction)
{
    int index = m_blockchain->getLastBlockIndex() + 1;
    QDateTime timestamp = QDateTime::currentDateTime();
    Transaction data = transaction;
    QByteArray prevHash = m_blockchain->getLastBlockHash();

    m_blockchain->addNextBlock(Block(index, prevHash, data, timestamp));
    emit updateTable();
}

int Miner::setGenesisBlock()
{
    if(m_blockchain->size() == 0){
        QDateTime timestamp = QDateTime::currentDateTime();
        QByteArray genesisHash = "816534932c2b7154836da6afc367695e6337db8a921823784c14378abed4f7d7";

        m_blockchain->addNextBlock(Block(0, genesisHash, Transaction(), timestamp));

        return 0;
    }
    return 1;
}

Blockchain* Miner::blockchain() const
{
    return m_blockchain;
}

void Miner::loadBlockchain(QString blockchain)
{
   m_blockchain->clear();
   if(!m_blockchain->fromString(blockchain))
       qDebug() << "void Miner::loadBlockchain(QString blockchain) : " << m_blockchain->getLastError() ;

}
