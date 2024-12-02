#pragma once

#include "socket.h"

#include <QDialog>
#include <QMessageBox>

namespace Ui {
 class CreateAccount;
}

namespace MS {
class CreateAccountDlg : public QDialog {
    Q_OBJECT

public:
    explicit CreateAccountDlg(QWidget *parent = nullptr);
    ~CreateAccountDlg();

    void init(std::shared_ptr<Socket> socket);

    bool createAcc(std::vector<QString>& userInfo);
    bool isRegistrated();

private slots:
    void on_createAccButton_clicked();

private:
    Ui::CreateAccount *ui;

    std::shared_ptr<Socket> socket_;

    std::vector<QString> userInfo;
    QString userLogin;
    QString userPassword;
    QString userEmail;
    bool isRegistrated_ = false;
};
}

