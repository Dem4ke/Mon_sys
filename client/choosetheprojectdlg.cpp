#include "choosetheprojectdlg.h"
#include "ui_choosetheprojectdlg.h"

namespace MS {
ChooseTheProjectDlg::ChooseTheProjectDlg(QWidget *parent) :
    QDialog(parent), ui(new Ui::ChooseTheProject) {

    ui->setupUi(this);
    setWatersList();
}

ChooseTheProjectDlg::~ChooseTheProjectDlg() {
    delete ui;
}

// Initialization of information about waters
void ChooseTheProjectDlg::init(std::shared_ptr<Socket> socket) {
    socket_ = socket;
    socket_->setWatersNamesRequest();
}

void ChooseTheProjectDlg::setWatersList() {
    watersNames_ = socket_->getWatersNames();

    for (int i = 0, end = watersNames_.size(); i < end; ++i) {
        ui->watersNameList->addItem(watersNames_[i]);
    }
}

QVector<QString> ChooseTheProjectDlg::getProjectInfo() const {
    QVector<QString> projectInfo = socket_->getWaterInfo();
    return projectInfo;
}

bool ChooseTheProjectDlg::isAccepted() const {
    return isAccepted_;
}

void ChooseTheProjectDlg::on_choiceOfWater_clicked() {
    isAccepted_ = true;
    currentProject_ = ui->watersNameList->currentItem()->text();
    socket_->setWaterInfoRequest(currentProject_);
    this->close();
}
}
