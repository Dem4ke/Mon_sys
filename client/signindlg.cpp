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

bool SignInDlg::isRegistrated() const {
    socket_->waitForReadyRead();
    qDebug() << "check is user exists";
    if (socket_->isUserExists()) {

        return true;
    }

    return false;
}

bool SignInDlg::isAccepted() const {
    return isAccepted_;
}

// Sign in user in a system
void SignInDlg::on_signInButton_clicked() {
    // Set information of user
    QVector<QString> userInfo;
    userInfo.clear();

    userLogin_ = ui->userLogin->text();
    userPassword_ = ui->userPassword->text();

    userInfo.push_back(userLogin_);
    userInfo.push_back(userPassword_);

    // Make a request to server for check user statement
    socket_->checkUserStatement(userInfo);



    isAccepted_ = true;
    this->close();
}
}
