#include "choosetheprojectdlg.h"
#include "ui_choosetheprojectdlg.h"

namespace MS {
ChooseTheProjectDlg::ChooseTheProjectDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChooseTheProject) {

    ui->setupUi(this);
}

ChooseTheProjectDlg::~ChooseTheProjectDlg() {
    delete ui;
}

// Initialization of information about waters
void ChooseTheProjectDlg::init(QTcpSocket* socket) {
    socket_ = socket;
    setWatersNamesRequest();
}

void ChooseTheProjectDlg::setWatersNamesRequest() {
    QVector<QString> info;
    sendToServer(3, info);
}

QVector<QString> ChooseTheProjectDlg::getProjectInfo() const {
    return waterInfo_;
}

bool ChooseTheProjectDlg::isAccepted() const {
    return isAccepted_;
}

void ChooseTheProjectDlg::on_choiceOfWater_clicked() {
    isAccepted_ = true;

    // Make request to get information about chosen water
    QVector<QString> chosenWater;
    chosenWater.push_back(ui->watersNameList->currentItem()->text());

    sendToServer(4, chosenWater);
}

//--------------------------------------------------------------------------------------------------------------------------
// SERVER TOOLS

// Handler of a client's messages
void ChooseTheProjectDlg::slotReadyRead() {
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

            if (flag == 3) {
                watersNames_ = info;

                // Set waters names in ui
                for (int i = 0, end = watersNames_.size(); i < end; ++i) {
                    ui->watersNameList->addItem(watersNames_[i]);
                }
            }
            else if (flag == 4) {
                waterInfo_ = info;
                this->close();
            }

            blockSize_ = 0;
            break;
        }
    }
}

void ChooseTheProjectDlg::sendToServer(int flag, QVector<QString> output) {
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

