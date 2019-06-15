/**
 * @file mainwindow.cpp
 * @brief This class implements GUI for our app using qt library
 * mainwindow.ui is the XML form file representing the GUI
 *
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;
/**
 * @brief Construct a MainWindow object for the application GUI. This window will be the parent window.
 *
 * @param *parent
 */
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow)
{
    //Setting up the main window for the application
    //Window is borderless and has a fixed size of 600x600
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(600, 600);

    //check for internet connection and pull data then fill the window
    Model* model = new Model();
    Controller* controller = new Controller(model);
    if (checkConnection())
    {
        controller->checkForUpdates();\
        populateField(model);
    }

    //a timer object to implement autoupdate
    QTimer *weather_timer = new QTimer(this);
    connect(weather_timer, SIGNAL(timeout()), this, SLOT(autoUpdate()));
    weather_timer->start(60000);

    //clear memory
    delete model;
    delete controller;

    //close and minimize button
    ui->closebtn->setStyleSheet("QPushButton {border-image:url(:/image/close.png);}QPushButton:hover{border-image:url(:/image/close1.png);}QPushButton:hover:pressed{border-image:url(:/image/close.png);}");
    ui->minbtn->setStyleSheet("QPushButton {border-image:url(:/image/min.png);}QPushButton:hover{border-image:url(:/image/min1.png);}QPushButton:hover:pressed{border-image:url(:/image/min.png);}");

    //When update button is clicked, request and display information
    connect(ui->updatebtn, SIGNAL(clicked()), SLOT(updatebtnClicked()));
    connect(ui->language, SIGNAL(currentTextChanged(QString)), this, SLOT(updateLanguage(QString)));

    //a timer object to implement a digital clock utility
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000);

    //a date object to implement a date utility
    QDateTime date = QDateTime::currentDateTime();
    ui->date->setText(tr("%1").arg(date.toString("MM/dd")));

}
/**
 * @brief Destrucrtor method. Destroys the MainWindow object and Model, Controller objects associated with it.
 *
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete controller;

}
/**
 * @brief A private slots method. when the update weather button is clicked. application will update the data with
 * newly entered location. This location comes from the search QLineEdit.
 *
 */
void MainWindow::updatebtnClicked()
{
    checkConnection();
    Model* mod = new Model();
    Controller* cont = new Controller(mod);
    int temp;
    string lang = "e";
    //change the current location and language according to the selection
    temp = cont->changeLocation(ui->search->text().toStdString());
    if (ui->language->currentText().toStdString() == "Francais") lang = "f";
    cont->changeLanguage(lang);
    //if location is invalid a pop-up window is created
    if (temp == 0)
    {
        QMessageBox::information(this, tr("Error"), tr("You have entered an invalid location!"), QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
        populateField(mod);
    }
    //free up memory
    delete mod;
    delete cont;

}
/**
 * @brief A private slots method. When the language selection is updated. Application will update the data
 * in the newly selected language and currect location.
 * The language input comes from the language QComboBox.
 *
 * @param lang
 */
void MainWindow::updateLanguage(QString lang)
{
    if (checkConnection())
    {
        Model* mod = new Model();
        Controller* cont = new Controller(mod);
        QString location = ui->search->text();
        //change the current language according to the selection
        if (lang == "Francais")
        {
            cont->changeLocation(location.toStdString());
            cont->changeLanguage("f");
            populateField(mod);
        }
        else if (lang == "English")
        {
            cont->changeLocation(location.toStdString());
            cont->changeLanguage("e");
            populateField(mod);

        }else
        {
            QMessageBox::information(this, tr("Error"), tr("There has been an error!"), QMessageBox::Ok, QMessageBox::Ok);
        }
        //free up memory
        delete mod;
        delete cont;
    }

}
/**
 * @brief A private method. This method populates all of the widgets and text browser with data
 * @param m
 */
void MainWindow::populateField(Model *m)
{
    ui->warnings->setText(QString::fromStdString(m->getWarning()));
    ui->location->setText(QString::fromStdString(m->getRegion()));
    ui->tabWidget->setTabText(0, QString::fromStdString(m->getForecastPeriod()[0]));
    ui->temperature->setText(QString::fromStdString(m->getForecastTemperatureSummary()[0]));
    ui->summary->setText(QString::fromStdString(m->getForecastLongSummary()[0]));

    ui->location_2->setText(QString::fromStdString(m->getRegion()));
    ui->tabWidget->setTabText(1, QString::fromStdString(m->getForecastPeriod()[1]));
    ui->temperature_2->setText(QString::fromStdString(m->getForecastTemperatureSummary()[1]));
    ui->summary_2->setText(QString::fromStdString(m->getForecastLongSummary()[1]));

    ui->location_3->setText(QString::fromStdString(m->getRegion()));
    ui->tabWidget->setTabText(2, QString::fromStdString(m->getForecastPeriod()[2]));
    ui->temperature_3->setText(QString::fromStdString(m->getForecastTemperatureSummary()[2]));
    ui->summary_3->setText(QString::fromStdString(m->getForecastLongSummary()[2]));

    ui->location_7->setText(QString::fromStdString(m->getRegion()));
    ui->tabWidget->setTabText(3, QString::fromStdString(m->getForecastPeriod()[3]));
    ui->temperature_7->setText(QString::fromStdString(m->getForecastTemperatureSummary()[3]));
    ui->summary_7->setText(QString::fromStdString(m->getForecastLongSummary()[3]));

    ui->location_8->setText(QString::fromStdString(m->getRegion()));
    ui->tabWidget->setTabText(4, QString::fromStdString(m->getForecastPeriod()[4]));
    ui->temperature_8->setText(QString::fromStdString(m->getForecastTemperatureSummary()[4]));
    ui->summary_8->setText(QString::fromStdString(m->getForecastLongSummary()[4]));

    ui->location_9->setText(QString::fromStdString(m->getRegion()));
    ui->tabWidget->setTabText(5, QString::fromStdString(m->getForecastPeriod()[5]));
    ui->temperature_9->setText(QString::fromStdString(m->getForecastTemperatureSummary()[5]));
    ui->summary_9->setText(QString::fromStdString(m->getForecastLongSummary()[5]));

    ui->location_10->setText(QString::fromStdString(m->getRegion()));
    ui->tabWidget->setTabText(6, QString::fromStdString(m->getForecastPeriod()[6]));
    ui->temperature_10->setText(QString::fromStdString(m->getForecastTemperatureSummary()[6]));
    ui->summary_10->setText(QString::fromStdString(m->getForecastLongSummary()[6]));

}
/**
 * @brief A private method. This method implements a digital clock utility
 *
 */
void MainWindow::updateTime()
{
    QTime time = QTime::currentTime();
    QString time_string = time.toString();
    ui->time_label->setText(time_string);

}
/**
 * @brief A private sltos method. This method implements auto updating
 *
 */
void MainWindow::autoUpdate()
{
    if(checkConnection())
    {
        controller->checkForUpdates();
        populateField(model);
    }

}
/**
 * @brief A private method. This method implements a internet-connection checking utility.
 * This method will try to access to google.ca to see if internet connection is active.
 * If no connection, a pop-up window is created.
 *
 */
int MainWindow::checkConnection()
{
    //send a request to google.ca, if no reply, there is no connection
    QNetworkAccessManager *nam = new QNetworkAccessManager();
    QNetworkReply *reply;
    QEventLoop loop;
    reply = nam->get(QNetworkRequest(QUrl("https://www.google.ca")));
    QTimer t;
    t.setSingleShot(true);
    connect(&t, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    t.start(5000);
    loop.exec();
    //create error message
    if (t.isActive())
    {
        t.stop();
        return 1;
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("You have no internet connection!"), QMessageBox::Ok, QMessageBox::Ok);
    }
    return 0;

}
