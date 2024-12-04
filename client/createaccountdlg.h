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

    bool isRegistrated() const;
    bool isAccepted() const;

private slots:
    void on_createAccButton_clicked();

private:
    Ui::CreateAccount *ui;
    bool isAccepted_ = false;

    std::shared_ptr<Socket> socket_;

    QString userLogin;
    QString userPassword;
    QString userEmail;
};
}

