#include "transaction.h"

#include <QStringList>


Transaction::Transaction(QString sender, QString reciepient, double amount)
{
    m_sender = sender ;
    m_reciepient = reciepient;
    m_amount = amount ;
}

double Transaction::amount() const
{
    return m_amount;
}

QString Transaction::sender() const
{
    return m_sender;
}

QString Transaction::reciepient() const
{
    return m_reciepient;
}

QString Transaction::toString() const
{
    return QString(m_sender+"|"+m_reciepient+"|"+QString::number(m_amount));
}

bool Transaction::fromString(QString transaction)
{
    QStringList tmp = transaction.split("|");
    if(tmp.length() != 3 )
    {
        m_lastError = "after split string it doesn't have size of transaction: transaction.split(\"|\").length() =" + QString::number(tmp.length()) ;
        return false ;
    }
    m_sender = tmp.at(0);
    m_reciepient = tmp.at(1) ;
    bool ok ;
    double d ;
    d = tmp.at(2).toDouble(&ok); // check if it convert to double without error
    if(!ok)
    {
        m_lastError = "error converting String to double: "+tmp.at(2);
        return false ; // if error converting string to double then return  false
    }

    m_amount = d ;
    return true ;
}

QString Transaction::lastError() const
{
    return m_lastError;
}
