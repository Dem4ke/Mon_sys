#include "mainwindow.h"
#include "./ui_mainwindow.h"

namespace MS {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // Create of connection socket
    socket_ = std::make_shared<Socket>();
}

MainWindow::~MainWindow() {
    delete ui;
}

// Show sing in window
void MainWindow::on_singIn_clicked() {
    signInDlg_ = new SignInDlg;

    signInDlg_->init(socket_);
    signInDlg_->setModal(true);
    signInDlg_->exec();

    if (signInDlg_->isRegistered()) {
        delete signInDlg_;
        //hide();

        //workWindow_ = new WorkWindow;
        //workWindow_->show();
    }
}

// Show account create window
void MainWindow::on_createAcc_clicked() {
    /*createAcc->setModal(true);
    createAcc->exec();
    if (createAcc->getUserStatus()) {
        delete createAcc;
        hide();
        workWindow->show();
    }*/
}
}

