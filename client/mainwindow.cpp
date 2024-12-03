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

    if (signInDlg_->isAccepted()) {
        if (signInDlg_->isRegistrated()) {
            delete signInDlg_;
            //hide();
            //workWindow->show();
        }
        else {
            signInDlg_->exec();
        }
    }
}

// Show account create window
void MainWindow::on_createAcc_clicked() {
    createAccDlg_ = new CreateAccountDlg;

    createAccDlg_->init(socket_);
    createAccDlg_->setModal(true);
    createAccDlg_->exec();

    if (createAccDlg_->isAccepted()) {
        if (createAccDlg_->isRegistrated()) {
            delete createAccDlg_;
            //hide();
            //workWindow->show();
        }
        else {
            createAccDlg_->exec();
        }
    }


    /*if (createAccDlg_->getUserStatus()) {
        delete createAccDlg_;
        hide();
        workWindow->show();
    }*/
}
}

