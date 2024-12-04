#include "choosetheprojectdlg.h"
#include "ui_choosetheprojectdlg.h"

namespace MS {
ChooseTheProject::ChooseTheProject(QWidget *parent) :
    QDialog(parent), ui(new Ui::ChooseTheProject) {

    ui->setupUi(this);
    setWatersList();
}

ChooseTheProject::~ChooseTheProject() {
    delete ui;
}

// Initialization of information about waters
void ChooseTheProject::init(std::shared_ptr<Socket> socket) {
    socket_ = socket;
    socket_->setWatersNamesRequest();
}

void ChooseTheProject::setWatersList() {
    watersNames_ = socket_->getWatersNames();

    for (int i = 0, end = watersNames_.size(); i < end; ++i) {
        ui->watersNameList->addItem(watersNames_[i]);
    }
}

QString ChooseTheProject::getProjectName() const {
    return currentProject_;
}

bool ChooseTheProject::isAccepted() const {
    return isAccepted_;
}

void ChooseTheProject::on_choiceOfWater_clicked() {
    currentProject = ui->watersNameList->currentItem()->text();
    projectChoosen = true;
    this->close();
}
}
