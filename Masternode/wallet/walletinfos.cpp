#include "walletinfos.h"

WalletInfos::WalletInfos( QObject *parent) : QObject(parent)
{
    lock = new QMutex ;

}

void WalletInfos::addNextWalletInfo(WalletInfo wi)
{
    lock->lock();
    m_walletinfos.append(wi);
    lock->unlock();
    emit datachanged();
}
