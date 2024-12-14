#include "mainwindow.h"
#include "./ui_mainwindow.h"

namespace MS {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // Connect application to server
    socket_ = new QTcpSocket(this);

    connect(socket_, &QTcpSocket::disconnected, socket_, &QTcpSocket::deleteLater);
    socket_->connectToHost("127.0.0.1", 2323);
}

MainWindow::~MainWindow() {
    delete ui;
}

// Show sing in window
void MainWindow::on_singIn_clicked() {
    signInDlg_ = new SignInDlg;
    connect(socket_, &QTcpSocket::readyRead, signInDlg_, &SignInDlg::slotReadyRead);

    signInDlg_->init(socket_);
    signInDlg_->setModal(true);
    signInDlg_->exec();

    if (signInDlg_->isRegistrated()) {
        delete signInDlg_;
        hide();

        workWindow_ = new WorkWindow;
        workWindow_->init(socket_);
        workWindow_->show();
    }
}

// Show account create window
void MainWindow::on_createAcc_clicked() {
    createAccDlg_ = new CreateAccountDlg;
    connect(socket_, &QTcpSocket::readyRead, createAccDlg_, &CreateAccountDlg::slotReadyRead);

    createAccDlg_->init(socket_);
    createAccDlg_->setModal(true);
    createAccDlg_->exec();

    if (createAccDlg_->isRegistrated()) {
        delete createAccDlg_;
        hide();

        workWindow_ = new WorkWindow;
        workWindow_->init(socket_);
        workWindow_->show();
    }
}
}

