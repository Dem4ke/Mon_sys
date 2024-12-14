#pragma once

#include <QDialog>
#include <QMessageBox>
#include <QTcpSocket>

namespace Ui {
class SignIn;
}

namespace MS {
class SignInDlg : public QDialog {
    Q_OBJECT

public:
    explicit SignInDlg(QWidget *parent = nullptr);
    ~SignInDlg();

    void init(QTcpSocket* socket);

    bool isRegistrated() const;

public slots:
    // Server tools
    void slotReadyRead();

private:
    void sendToServer(int flag, QVector<QString> output);

private slots:
    void on_signInButton_clicked();

private:
    Ui::SignIn* ui;
    bool isRegistrated_ = false;

    QString userLogin_;
    QString userPassword_;

    quint16 blockSize_ = 0;         // Size of data package
    QTcpSocket* socket_;
    QByteArray data_;
};
}

