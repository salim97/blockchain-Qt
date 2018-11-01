#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QThread>
#include <miner.h>
#include <qDebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initAction();


    //creating blockchain ...
    blockchain = new Blockchain(this) ;

    //creating miner and passing copy of pointer to blockchain...
    miner = new Miner(blockchain, this) ;
    miner->setGenesisBlock();

    //creating list of wallets log
    walletInfos = new WalletInfos(this) ;

    //creating wallet server that communicate with client
    walletserver = new WalletServer(walletInfos, blockchain, this);



    miner->generateNextBlock(Transaction("salim", "hichem", 50));
    miner->generateNextBlock(Transaction("salim", "hichem", 50));
    miner->generateNextBlock(Transaction("salim", "hichem", 50));

    connect(blockchain, SIGNAL(datachanged()), this, SLOT(updateBlockchainTable()));
    connect(walletInfos, SIGNAL(datachanged()), this, SLOT(updateWalletInfoTable()));
    updateBlockchainTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateBlockchainTable()
{
    ui->tableWidget_blockchain->setRowCount(0);
    ui->tableWidget_blockchain->setRowCount(blockchain->length());

    for(int i = 0 ; i < blockchain->length() ; i++)
    {
        ui->tableWidget_blockchain->setItem(i, 0, new QTableWidgetItem(QString::number(blockchain->at(i).getIndex())));
        ui->tableWidget_blockchain->setItem(i, 1, new QTableWidgetItem(QString(blockchain->at(i).getPrevHash())));
        ui->tableWidget_blockchain->setItem(i, 2, new QTableWidgetItem(QString(blockchain->at(i).getCurrHash())));
        ui->tableWidget_blockchain->setItem(i, 3, new QTableWidgetItem(blockchain->at(i).getData().toString()));
        ui->tableWidget_blockchain->setItem(i, 4, new QTableWidgetItem(blockchain->at(i).getTimestamp().toString()));

    }
}

void MainWindow::updateWalletInfoTable()
{
    qDebug() << "updateWalletInfoTable" ;
    ui->tableWidget_wallet->setRowCount(0);
    ui->tableWidget_wallet->setRowCount(walletInfos->length());

    for(int i = 0 ; i < walletInfos->length() ; i++)
    {
        ui->tableWidget_wallet->setItem(i, 0, new QTableWidgetItem(walletInfos->at(i).remoteAddress));
        ui->tableWidget_wallet->setItem(i, 1, new QTableWidgetItem(walletInfos->at(i).userName));
        if(walletInfos->at(i).active)
            ui->tableWidget_wallet->setItem(i, 2, new QTableWidgetItem("true"));
        else
            ui->tableWidget_wallet->setItem(i, 2, new QTableWidgetItem("false"));

    }
}


/*------------UI STUFF ----------------*/

void MainWindow::initAction()
{

    // init widget action
    QAction  *supprime, *ajoute;
    supprime = new QAction("Supprime", this);
    ajoute = new QAction("ajoute", this);

    //Icon
    supprime->setIcon(QIcon("qrc:/icons/Delete-96.png"));
    ajoute->setIcon(QIcon("qrc:/icons/Delete-96.png"));

    // on click
    connect(supprime, SIGNAL(triggered(bool)), this, SLOT(del_item()));
    connect(ajoute, SIGNAL(triggered(bool)), this, SLOT(add_item()));

    // init table with action
    ui->tableWidget_blockchain->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableWidget_blockchain->addAction(ajoute);
    ui->tableWidget_blockchain->addAction(supprime);
}

void MainWindow::add_item()
{
    // TODO : add dialog to insert new transaction in block
    miner->generateNextBlock(Transaction("salim", "hichem", 50));
}

void MainWindow::del_item()
{
    // TODO : add dialog to ask user if he really want to delete this
    int currentRow = ui->tableWidget_blockchain->currentRow() ;
    QString data ;
    data += blockchain->at(currentRow).toString() ;
    //remove all separator from String
    data.replace("\\", "\n");
    data.replace("//", "\n");
    data.replace("||", "\n");

    bool yes = msgQuestion("Delete block", data);
    if(yes)
    {
        // we can add signal to blockchain emited when CURD ( create , update,  delete )....
        blockchain->removeAt(currentRow);
        ui->tableWidget_blockchain->removeRow(currentRow);
    }
}


bool MainWindow::msgQuestion(QString title ,QString body)
{
    qDebug() << "title: "+ title << "\nboady: "+ body ;
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(body);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
        return true ;
    }

    return false ;
}
