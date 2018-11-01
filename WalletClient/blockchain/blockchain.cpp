#include "blockchain.h"

Blockchain::Blockchain(QObject *parent) : QObject(parent)
{
    lock = new QMutex ;
}

int Blockchain::getLastBlockIndex() const
{
    return m_chain.last().getIndex();
}

QByteArray Blockchain::getLastBlockHash()
{
    return m_chain.last().getCurrHash();
}

QDateTime Blockchain::getLastBlockTimestamp() const
{
    return m_chain.last().getTimestamp();
}

void Blockchain::addNextBlock(Block block)
{
    lock->lock();
    m_chain.append(block); // section critique
    lock->unlock();
    emit datachanged();
}



int Blockchain::size() const
{
    return m_chain.size();
}

QString Blockchain::toString() const
{
    QString tmp ;
    for(int i = 0 ; i < m_chain.length() ; i++ )
    {
        tmp += m_chain.at(i).toString() + "\\";
    }
    return tmp ;
}

bool Blockchain::fromString(QString blockchain)
{
    QStringList tmp = blockchain.split("\\");
    Block block ;
    for(int i = 0 ; i < tmp.length() ; i++)
    {
        if(block.fromString(tmp.at(i)))
            m_chain.append(block);
        else
        {
            m_lastError = block.getLastError() ;
            return false ;
        }
    }

    return true ;
}

QString Blockchain::getLastError() const
{
    return m_lastError;
}

QVector<Block> Blockchain::getChain() const
{
    return m_chain;
}

