#pragma once

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class ChooseTheProject;
}

namespace MS {
class ChooseTheProjectDlg : public QDialog {
    Q_OBJECT

public:
    explicit ChooseTheProjectDlg(QWidget *parent = nullptr);
    ~ChooseTheProjectDlg();

    void init(QTcpSocket* socket);

    void setWatersNamesRequest();
    QVector<QString> getProjectInfo() const;

    bool isAccepted() const;

public slots:
    // Server tools
    void slotReadyRead();

private:
    void sendToServer(int flag, QVector<QString> output);

private slots:
    void on_choiceOfWater_clicked();

private:
    Ui::ChooseTheProject *ui;
    bool isAccepted_ = false;

    QVector<QString> watersNames_;
    QVector<QString> waterInfo_;        // Information about water

    QTcpSocket* socket_;                // Socket which uses to work with server
    quint16 blockSize_ = 0;             // Size of data package
    QByteArray data_;
};
}

