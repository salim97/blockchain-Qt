#ifndef BLOCK_H
#define BLOCK_H



#include <QByteArray>
#include <QDateTime>
#include <QCryptographicHash>

#include "transaction.h"

class Block
{

public:
    Block() ;
    explicit Block(int index, QByteArray prevHash,Transaction data, QDateTime timestamp);

    int getIndex() const;
    QByteArray getPrevHash() const;

    Transaction getData() const;
    QDateTime getTimestamp() const;

    QByteArray getCurrHash() const;

    //we need those two method for sending and recieving this over network
    QString toString() const;
    bool fromString(QString block) ;
    QString getLastError() const;

private:
    int m_index;            // position in blockchain
    QByteArray m_prevHash;  // prevuse block hash
    QByteArray m_currHash;  // current block hash
    Transaction m_data;     // data
    QDateTime m_timestamp;  // time stamp


    QString m_lastError ;
};

#endif // BLOCK_H
