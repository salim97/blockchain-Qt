#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>



class Transaction
{
public:

    Transaction(QString sender = "", QString reciepient ="", double amount = 0.0);

    double amount() const;
    QString sender() const;
    QString reciepient() const;

    //we need those two method for sending and recieving this over network
    QString toString() const; // get sender + reciepient + amount in one line string
    bool fromString(QString transaction) ;// from string to Transaction

    QString lastError() const;

private:
    // i use _ to specifai that it's private variable
    QString m_sender, m_reciepient ;
    double m_amount ;
    QString m_lastError ;
};

#endif // TRANSACTION_H
