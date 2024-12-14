#include "workwindow.h"
#include "ui_workwindow.h"
#include <sstream>
#include <locale>
#include <iomanip>

namespace MS {
WorkWindow::WorkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WorkWindow) {

    ui->setupUi(this);
}

WorkWindow::~WorkWindow() {
    delete ui;
}

// Initialization of socket
void WorkWindow::init(QTcpSocket* socket) {
    socket_ = socket;
}

// Ask to server about data of project, then draw it in client
// Draw graph of water level in water
void WorkWindow::drawWaterLevelPlots() {
    // Set locate to Russian, get russian month names
    ui->plot->setLocale(QLocale(QLocale::Russian, QLocale::RussianFederation));

    // Create graph
    ui->plot->addGraph();

    // Refactor data to plots
    QVector<QCPGraphData> valueWithDate(currentProject.size());

    // Assign data to graph
    for (int i = 0, end = currentProject.size(); i < end; ++i) {
        // Days in a seconds (3600 * 24 = 86400 - one day)
        valueWithDate[i].key = currentProject[i].first;
        valueWithDate[i].value = currentProject[i].second;
    }

    ui->plot->graph()->data()->set(valueWithDate);

    // Add minimum and maximum range of data
    double minDate = currentProject[0].first;
    double maxDate = currentProject[currentProject.size() - 1].first;

    double minLevelInMinDate = 0;
    double maxLevelInMaxDate = 1000;

    // Configure bottom axis to show date
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("d.MMMM\nyyyy");
    ui->plot->xAxis->setTicker(dateTicker);

    // Add labels
    ui->plot->xAxis->setLabel("Date");
    ui->plot->yAxis->setLabel("Level of water, mm");

    // Set visible range
    ui->plot->xAxis->setRange(minDate, maxDate);
    ui->plot->yAxis->setRange(minLevelInMinDate, maxLevelInMaxDate);

    // Add ability to move area by LBM, zoom graph with mouse weel, to select graph by LMB
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->plot->replot();
}

void WorkWindow::drawBeaufortScalePlots() {
    // Refactor data to plots
    /*QVector<double> date; // Horizontal
    QVector<double> levels; // Vertical

    for (auto& i : currentProject) {
        double first = i.first.toDouble();
        double second = i.second.toDouble();

        date.push_back(first);
        levels.push_back(second);
    }

    // Add minimum and maximum range of data
    double minDate = date[0];
    double maxDate = date[date.size() - 1];

    double minLevelInMinDate = server.minValue(levels) - (server.minValue(levels) / 10);
    double maxLevelInMaxDate = server.maxValue(levels);

    // Create graph and assign data to it
    ui->plot->addGraph();
    ui->plot->graph(0)->setData(date, levels);

    // Add labels
    ui->plot->xAxis->setLabel("Date");
    ui->plot->yAxis->setLabel("Ball of Beaufort");

    // Set visible range
    ui->plot->xAxis->setRange(minDate, maxDate);
    ui->plot->yAxis->setRange(minLevelInMinDate, maxLevelInMaxDate);

    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->plot->replot();*/
}

// Choose the project and main work logic
void WorkWindow::on_actionOpen_project_triggered() {
    chooseTheProjectDlg_ = new ChooseTheProjectDlg;
    connect(socket_, &QTcpSocket::readyRead, chooseTheProjectDlg_, &ChooseTheProjectDlg::slotReadyRead);

    chooseTheProjectDlg_->init(socket_);

    chooseTheProjectDlg_->setModal(true);
    chooseTheProjectDlg_->exec();

    if (chooseTheProjectDlg_->isAccepted()) {
        // Get info from database
        projectInfo_ = chooseTheProjectDlg_->getProjectInfo();

        // Set water level
        waterLevelLimit_ = projectInfo_[0].toInt();

        // Set pairs of X, Y axis
        currentProject.clear();

        for (int i = 1, end = projectInfo_.size(); i < end; i += 2) {
            std::pair<int, int> axis;

            axis.first = getTimeFromString(projectInfo_[i]);
            axis.second = projectInfo_[i + 1].toInt();

            currentProject.push_back(axis);
        }

        // Draw plots for default
        drawWaterLevelPlots();
    }

    delete chooseTheProjectDlg_;
}

// Log out ability to user, he can change his level
void WorkWindow::on_actionLog_out_triggered() {
    this->close();
}

// Change plot to level of water
void WorkWindow::on_waterLevelButton_clicked() {

}


void WorkWindow::on_beaufordScaleButton_clicked() {

}

//----------------------------------------------------------------------
// PRIVATE WORK TOOLS
int WorkWindow::getTimeFromString(QString date) {
    std::tm t = {};
    std::istringstream ss(date.toStdString());
    int time = 0;

    if (ss >> std::get_time(&t, "%Y-%m-%d")) {
        time = std::mktime(&t);
    }

    return time;
}

int WorkWindow::currentProjectMinValue() {
    double min = currentProject[0].first;

    for (auto& i : currentProject) {
        if (min > i.first) {
            min = i.first;
        }
    }

    return min;
}

int WorkWindow::currentProjectMaxValue() {
    double max = currentProject[0].first;

    for (auto& i : currentProject) {
        if (max < i.first) {
            max = i.first;
        }
    }

    return max;
}
}

