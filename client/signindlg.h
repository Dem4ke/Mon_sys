#pragma once

#include <QDialog>
#include <QMessageBox>
#include "socket.h"

namespace Ui {
 class SignIn;
}

namespace MS {
class SignInDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SignInDlg(QWidget *parent = nullptr);
    ~SignInDlg();

    void init(std::shared_ptr<Socket> socket);
    bool isRegistered();

private slots:
    void on_signInButton_clicked();

private:
    Ui::SignIn* ui;

    bool isRegistered_ = false;

    QString userLogin_;
    QString userPassword_;
    std::vector<QString> userInfo_;

    std::shared_ptr<Socket> socket_;
};
}

