#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/**
 * @file mainwindow.h
 *
 */
#include <QMainWindow>
#include "backend/Model.h"
#include "backend/Controller.h"
#include <QTimer>
#include <QTime>
#include <string>
#include <QMessageBox>
#include <QUrl>
#include <QtNetwork>
#include <QDebug>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateLanguage(QString);
    void updatebtnClicked();

private slots:
    void updateTime();
    void autoUpdate();

private:
    Ui::MainWindow *ui;
    Model *model;
    Controller *controller;

    void populateField(Model*);
    int checkConnection();
};

#endif //MAINWINDOW_H
