#include "block.h"
#include <qdebug.h>

Block::Block()
{

}

Block::Block(int index, QByteArray prevHash, Transaction data, QDateTime timestamp)
{
    m_index = index ;
    m_prevHash = prevHash;
    m_data = data;
    m_timestamp = timestamp;
}

int Block::getIndex() const { return m_index; }

QByteArray Block::getPrevHash() const { return m_prevHash; }

QByteArray Block::getCurrHash() const{
    QString tmp ;
    tmp += QString::number(m_index) ;
    tmp += m_prevHash ;
    tmp += m_data.toString() ;
    tmp += m_timestamp.toString() ;

    //m_currHash =
    return QCryptographicHash::hash( tmp.toUtf8(), QCryptographicHash::Sha256).toHex();;
}

Transaction Block::getData() const { return m_data; }

QDateTime Block::getTimestamp() const { return m_timestamp; }

QString Block::toString() const
{
    QString tmp ;
    tmp += QString::number(m_index) + "//" ;
    tmp += m_prevHash + "//" ;
    tmp += getCurrHash() + "//" ;
    tmp += m_data.toString() + "//" ;
    tmp += m_timestamp.toString()  ;
    return tmp ;
}

bool Block::fromString(QString block)
{
    QStringList tmp = block.split("//");
    if(tmp.length() != 5 )
    {
        m_lastError = "after split string it doesn't have size of block: block.split(\"//\").length() =" + QString::number(tmp.length()) ;
        return false ;
    }

    m_index = tmp.at(0).toInt();
    m_prevHash = tmp.at(1).toUtf8() ;
    m_currHash = tmp.at(2).toUtf8() ;
    m_data.fromString( tmp.at(3) );
    m_timestamp.fromString( tmp.at(4) );

    return true ;
}

QString Block::getLastError() const
{
    return m_lastError;
}

