#pragma once

#include <QMainWindow>
#include "signindlg.h"
#include "createaccountdlg.h"
#include "workwindow.h"

namespace Ui {
class MainWindow;
}

namespace MS {
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_singIn_clicked();
    void on_createAcc_clicked();

private:
    // Network tools
    QTcpSocket* socket_;                // Socket which uses to work with server

private:
    // Dialogs and UI
    Ui::MainWindow* ui;
    SignInDlg* signInDlg_;              // Dialog which uses to sign in user's account
    CreateAccountDlg* createAccDlg_;    // Dialog which uses to create new account
    WorkWindow* workWindow_;            // Window with main work functions
};
}

