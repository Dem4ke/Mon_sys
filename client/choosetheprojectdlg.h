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
    explicit ChooseTheProjectDlg(QWidget *parent = nullptr);
    ~ChooseTheProjectDlg();

    void init(std::shared_ptr<Socket> socket);

    void setWatersList();
    QVector<QString> getProjectInfo() const;

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
