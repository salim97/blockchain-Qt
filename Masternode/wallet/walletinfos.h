#ifndef WALLETINFOS_H
#define WALLETINFOS_H

#include <QMutex>
#include <QObject>

class WalletInfo{

public:

    QString remoteAddress, userName;
    bool active= false;
};

class WalletInfos : public QObject
{
    Q_OBJECT
public:
    explicit WalletInfos(QObject *parent = nullptr);


    // TODO : Replace those lines ...
    void clear()        {  m_walletinfos.clear(); }
    WalletInfo at(int index) { return m_walletinfos.at(index) ; }
    int length()        { return m_walletinfos.length() ;}
    void removeAt(int index) { return m_walletinfos.removeAt(index) ; }
    void addNextWalletInfo(WalletInfo wi);
signals:
    void datachanged() ;
public slots:

private:
    QList<WalletInfo> m_walletinfos ;
    QMutex *lock; // exclution mutual
};

#endif // WALLETINFOS_H
