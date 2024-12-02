#include "createaccountdlg.h"
#include "ui_createaccount.h"

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

// Make a request to server for add the user
bool CreateAccountDlg::createAcc(std::vector<QString>& userInfo) {
    socket_->checkUserStatement(userInfo);

    // If user doesn't exist we create a new account
    if (!socket_->isUserExists()) {
        socket_->addUser(userInfo);
        return true;
    }

    return false;
}

bool CreateAccountDlg::isRegistrated() {
    return isRegistrated_;
}

void CreateAccountDlg::on_createAccButton_clicked() {
    // Set information of user
    userInfo.clear();

    userLogin = ui->userLogin->text();
    userInfo.push_back(userLogin);

    userPassword = ui->userPassword->text();
    userInfo.push_back(userPassword);

    userEmail = ui->userEmail->text();
    userInfo.push_back(userEmail);

    // Make a request to server for add the user
    if (createAcc(userInfo)) {
        QMessageBox::information(this, "Success","Account has been created");
        isRegistrated_ = true;
        this->close();
    }
    else {
        QMessageBox::warning(this, "Denied","User with same login exist");
    }
}
}

