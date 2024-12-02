#pragma once
/*
#include "choosetheproject.h"
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

     void drawWaterLevelPlots(QString project);
     void drawBeaufortScalePlots(QString project);
     bool isUserWantToLeave();

 private slots:
     void on_actionOpen_project_triggered();
     void on_actionLog_out_triggered();
     void on_waterLevelButton_clicked();

     void on_beaufordScaleButton_clicked();

 private:
     Ui::WorkWindow *ui;
     ChooseTheProject *chooseTheProject;

     QVector<std::pair<QString, QString>> currentProject;
     bool changeAccount = false;
     QString project;
     Server server;
 };
}
*/
