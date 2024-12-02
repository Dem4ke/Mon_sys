/*#include "workwindow.h"
#include "ui_workwindow.h"

namespace MS {
WorkWindow::WorkWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::WorkWindow),
    chooseTheProject(new ChooseTheProject(parent)) {
    ui->setupUi(this);
}

WorkWindow::~WorkWindow() {
    delete ui;
    delete chooseTheProject;
}

// Ask to server about data of project, then draw it in client
// Draw graph of water level in water
void WorkWindow::drawWaterLevelPlots(QString project) {
    currentProject.clear();
    server.openProject(project, currentProject);

    // Set locate to Russian, get russian month names
    ui->plot->setLocale(QLocale(QLocale::Russian, QLocale::RussianFederation));

    // Create graph
    ui->plot->addGraph();

    // Refactor data to plots
    QVector<QCPGraphData> valueWithDate(currentProject.size());

    // Assign data to graph
    for (int i = 0, end = currentProject.size(); i < end; ++i) {
        // Days in a seconds (3600 * 24 = 86400 - one day)
        valueWithDate[i].key = currentProject[i].first.toInt();
        valueWithDate[i].value = currentProject[i].second.toDouble();
    }

    ui->plot->graph()->data()->set(valueWithDate);

    // Add minimum and maximum range of data
    double minDate = currentProject[0].first.toDouble();
    double maxDate = currentProject[currentProject.size() - 1].first.toDouble();

    // Convert information of project from QStirng to double
    QVector<double> projectData;
    for (auto& i : currentProject) {
        projectData.push_back(i.second.toDouble());
    }

    double minLevelInMinDate = server.minValue(projectData) - (server.minValue(projectData) / 10);
    double maxLevelInMaxDate = server.maxValue(projectData);

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

void WorkWindow::drawBeaufortScalePlots(QString project) {
    currentProject.clear();
    server.openProject(project, currentProject);

    // Refactor data to plots
    QVector<double> date; // Horizontal
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

    ui->plot->replot();
}

bool WorkWindow::isUserWantToLeave() { return changeAccount; }

// Choose the project and main work logic
void WorkWindow::on_actionOpen_project_triggered() {
    chooseTheProject->setModal(true);
    chooseTheProject->exec();

    if (chooseTheProject->isProjectChoosen()) {
        project = chooseTheProject->getProjectName();
        drawWaterLevelPlots(project);
    }
}

// Log out ability to user, he can change his level
void WorkWindow::on_actionLog_out_triggered() {
    changeAccount = true;
    this->close();
}

// Change plot to level of water
void WorkWindow::on_waterLevelButton_clicked() {
    if (!project.isEmpty()) {
        drawWaterLevelPlots(project);
    }
}


void WorkWindow::on_beaufordScaleButton_clicked() {
    if (!project.isEmpty()) {
        drawBeaufortScalePlots(project);
    }
}
}
*/
