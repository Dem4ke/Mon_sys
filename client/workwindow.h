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

    void init(std::shared_ptr<Socket> socket);

    void drawWaterLevelPlots(QString project);
    void drawBeaufortScalePlots(QString project);
    bool isUserWantToLeave();

private slots:
    void on_actionOpen_project_triggered();
    void on_actionLog_out_triggered();
    void on_waterLevelButton_clicked();
    void on_beaufordScaleButton_clicked();

private:
    Ui::WorkWindow* ui;
    ChooseTheProjectDlg* chooseTheProjectDlg_;

    std::shared_ptr<Socket> socket_;

    QVector<std::pair<QString, QString>> currentProject;
    bool changeAccount = false;
    QString project;
    QVector<QString> projectInfo_;
};
}

