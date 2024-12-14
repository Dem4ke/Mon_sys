#pragma once

#include "choosetheprojectdlg.h"
#include "qcustomplot.h"

#include <QMainWindow>

namespace Ui {
class WorkWindow;
}

namespace MS {
class WorkWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit WorkWindow(QWidget *parent = nullptr);
    ~WorkWindow();

    void init(QTcpSocket* socket);

    void drawWaterLevelPlots();
    void drawBeaufortScalePlots();

private slots:
    void on_actionOpen_project_triggered();
    void on_actionLog_out_triggered();
    void on_waterLevelButton_clicked();
    void on_beaufordScaleButton_clicked();

private:
    // Plots tools
    int getTimeFromString(QString date);
    int currentProjectMinValue();
    int currentProjectMaxValue();

private:
    int waterLevelLimit_ = 0;

private:
    Ui::WorkWindow* ui;
    ChooseTheProjectDlg* chooseTheProjectDlg_;

    QTcpSocket* socket_;                // Socket which uses to work with server

    QVector<std::pair<int, int>> currentProject;

    QString project;
    QVector<QString> projectInfo_;
};
}

