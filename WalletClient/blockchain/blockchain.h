#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H


#include <QVector>
#include <QByteArray>
#include <QDateTime>
#include <QObject>
#include <QMutex>
#include "Block.h"

class Blockchain: public QObject
{
    Q_OBJECT
public:

    explicit Blockchain(QObject *parent = nullptr);

    int size() const;
    int getLastBlockIndex() const;
    QByteArray getLastBlockHash();
    QDateTime getLastBlockTimestamp() const;
    void addNextBlock(Block block);

    //we need those two method for sending and recieving this over network
    QString toString() const ;
    bool fromString(QString blockchain) ;

    QString getLastError() const;

    QVector<Block> getChain() const;

    // TODO : Replace those lines ...
    void clear()        {  m_chain.clear(); }
    Block at(int index) { return m_chain.at(index) ; }
    int length()        { return m_chain.length() ;}
    void removeAt(int index) { return m_chain.removeAt(index) ; }
signals:
    void datachanged() ;

private:
    QVector<Block> m_chain;
    QString m_lastError;
    QMutex *lock;

};

#endif // BLOCKCHAIN_H
