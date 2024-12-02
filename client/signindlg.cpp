#include "signindlg.h"
#include "ui_signindlg.h"

namespace MS {
SignInDlg::SignInDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignIn) {

    ui->setupUi(this);
}

SignInDlg::~SignInDlg() {
    delete ui;
}

// Initialization of information about users
void SignInDlg::init(std::shared_ptr<Socket> socket) {
    socket_ = socket;
}

bool SignInDlg::isRegistered() {
    return isRegistered_;
}

// Sign in user in a system
void SignInDlg::on_signInButton_clicked() {
    userInfo_.clear();

    userLogin_ = ui->userLogin->text();
    userPassword_ = ui->userPassword->text();

    userInfo_.push_back(userLogin_);
    userInfo_.push_back(userPassword_);

    if (socket_->checkUserStatement(userInfo_)) {
        isRegistered_ = true;
        this->close();
    }
    else {
        QMessageBox::warning(this, "Denied", "User or password is wrong");
    }
}
}
