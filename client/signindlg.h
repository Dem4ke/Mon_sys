#pragma once

#include <QDialog>
#include <QMessageBox>
#include "socket.h"

namespace Ui {
 class SignIn;
}

namespace MS {
class SignInDlg : public QDialog {
    Q_OBJECT

public:
    explicit SignInDlg(QWidget *parent = nullptr);
    ~SignInDlg();

    void init(std::shared_ptr<Socket> socket);

    bool isRegistrated() const;
    bool isAccepted() const;

private slots:
    void on_signInButton_clicked();

private:
    Ui::SignIn* ui;
    bool isAccepted_ = false;

    QString userLogin_;
    QString userPassword_;

    std::shared_ptr<Socket> socket_;
};
}

