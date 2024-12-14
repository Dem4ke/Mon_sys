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

void CreateAccountDlg::init(QTcpSocket* socket) {
    socket_ = socket;
}

bool CreateAccountDlg::isRegistrated() const {
    return isRegistrated_;
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
    sendToServer(1, userInfo);
}

//--------------------------------------------------------------------------------------------------------------------------
// SERVER TOOLS

// Handler of a client's messages
void CreateAccountDlg::slotReadyRead() {
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

            if (flag == 1) {
                if (info[0] == "denied") {
                    QMessageBox::warning(this, "Denied","User with this login exists");
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

void CreateAccountDlg::sendToServer(int flag, QVector<QString> output) {
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

