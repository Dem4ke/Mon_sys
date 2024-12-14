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
void SignInDlg::init(QTcpSocket* socket) {
    socket_ = socket;
}

bool SignInDlg::isRegistrated() const {
    return isRegistrated_;
}

// Sign in user in a system
void SignInDlg::on_signInButton_clicked() {
    // Set information of user
    QVector<QString> userInfo;

    userLogin_ = ui->userLogin->text();
    userPassword_ = ui->userPassword->text();

    userInfo.push_back(userLogin_);
    userInfo.push_back(userPassword_);

    // Make a request to server for check user statement
    sendToServer(2, userInfo);
}

//--------------------------------------------------------------------------------------------------------------------------
// SERVER TOOLS

// Handler of a client's messages
void SignInDlg::slotReadyRead() {
    QDataStream input(socket_);
    input.setVersion(QDataStream::Qt_6_7);

    if (input.status() == QDataStream::Ok) {
        while(true) {
            // Calculate size of the block of data
            if (blockSize_ == 0) {
                if (socket_->bytesAvailable() < 2) {
                    break;
                }

                // Write the block size
                input >> blockSize_;
            }

            // If the block size is bigger than data from server, we should wait to other data
            if (socket_->bytesAvailable() < blockSize_) {
                break;
            }

            // Write data from server
            QVector<QString> info;
            int flag;

            input >> flag >> info;

            if (flag == 2) {
                if (info[0] == "denied") {
                    QMessageBox::warning(this, "Denied","Login or password is wrong");
                }
                else if (info[0] == "success") {
                    isRegistrated_ = true;
                    this->close();
                }
            }

            blockSize_ = 0;
            break;
        }
    }
}

void SignInDlg::sendToServer(int flag, QVector<QString> output) {
    data_.clear();

    QDataStream out(&data_, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    // Calculate and write a size of the sent data package
    out << quint16(0) << flag << output;
    out.device()->seek(0);
    out << quint16(data_.size() - sizeof(quint16));

    // Send package
    socket_->write(data_);
}
}
