#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "miner.h"
#include "blockchain.h"
#include "walletinfos.h"
#include "walletserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateBlockchainTable();
    void updateWalletInfoTable();
    void add_item();
    void del_item();
private:
    Ui::MainWindow *ui;
    Blockchain *blockchain;
    WalletInfos *walletInfos ;
    WalletServer *walletserver;
    Miner *miner ;
    void initAction();

    bool msgQuestion(QString title, QString body);
};

#endif // MAINWINDOW_H
