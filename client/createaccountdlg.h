#pragma once

#include <QDialog>
#include <QMessageBox>
#include <QTcpSocket>

namespace Ui {
class CreateAccount;
}

namespace MS {
class CreateAccountDlg : public QDialog {
    Q_OBJECT

public:
    explicit CreateAccountDlg(QWidget *parent = nullptr);
    ~CreateAccountDlg();

    void init(QTcpSocket* socket);

    bool isRegistrated() const;

public slots:
    // Server tools
    void slotReadyRead();

private:
    void sendToServer(int flag, QVector<QString> output);

private slots:
    void on_createAccButton_clicked();

private:
    Ui::CreateAccount *ui;
    bool isRegistrated_ = false;

    QString userLogin;
    QString userPassword;
    QString userEmail;

    quint16 blockSize_ = 0;         // Size of data package
    QTcpSocket* socket_;
    QByteArray data_;
};
}
