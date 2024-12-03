#include "createaccountdlg.h"
#include "ui_createaccountdlg.h"

namespace MS {
CreateAccountDlg::CreateAccountDlg(QWidget *parent) :
    QDialog(parent), ui(new Ui::CreateAccount) {

    ui->setupUi(this);
}

CreateAccountDlg::~CreateAccountDlg() {
    delete ui;
}

void CreateAccountDlg::init(std::shared_ptr<Socket> socket) {
    socket_ = socket;
}

bool CreateAccountDlg::isRegistrated() {
    if (socket_->isUserExists()) {
        QMessageBox::information(this, "Success","Account has been created");
        return true;
    }
    else {
        QMessageBox::warning(this, "Denied","User with same login exists");
    }
    return false;
}

bool CreateAccountDlg::isAccepted() {
    return isAccepted_;
}

void CreateAccountDlg::on_createAccButton_clicked() {
    // Set information of user
    QVector<QString> userInfo;

    userLogin = ui->userLogin->text();
    userInfo.push_back(userLogin);

    userPassword = ui->userPassword->text();
    userInfo.push_back(userPassword);

    userEmail = ui->userEmail->text();
    userInfo.push_back(userEmail);

    // Make a request to server for add the user
    socket_->addUser(userInfo);

    isAccepted_ = true;
    this->close();
}
}

