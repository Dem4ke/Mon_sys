#pragma once

#include <QDialog>
#include "socket.h"

namespace Ui {
class ChooseTheProject;
}

namespace MS {
class ChooseTheProjectDlg : public QDialog {
    Q_OBJECT

public:
    explicit ChooseTheProject(QWidget *parent = nullptr);
    ~ChooseTheProject();

    void init(std::shared_ptr<Socket> socket);

    void setWatersList();
    QString getProjectName() const;

    bool isAccepted() const;

private slots:
    void on_choiceOfWater_clicked();

private:
    Ui::ChooseTheProject *ui;
    bool isAccepted_ = false;

    QString currentProject_;
    QVector<QString> watersNames_;
    std::shared_ptr<Socket> socket_;
};
}
