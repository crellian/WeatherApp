/**
 * @file test.cpp
 * @brief This function tests the controller methods and prints the corresponding data in the
 * model to the std out. Can be used as example for correct controller/model usage.
 *
 */
#include <iostream>
#include <string>
#include <vector>
#include "Model.h"
#include "Controller.h"
using namespace std;

/**
 * @brief This program will initially print the default info in the Model which
 * should be data in english from London, Ontario. The second group of data that
 * is printed to the screen is determined by the variables below. Change these
 * to determine what data in what language gets printed to the screen.
 *
 */
string location = "Toronto";
//Language options are only "e" and "f"
string language = "f";

int main()
{
    Model *model = new Model();
    Controller *controller = new Controller(model);

    //This portions just checks the defaults which should be data
    //in english from London, Ontario
    controller->checkForUpdates();
    cout << model->getRegion() << "\n"
         << model->getWarning() << "\n" << endl;
    for (int i = 0; i < model->getForecastPeriod().size(); i++)
    {
        cout << model->getForecastPeriod()[i]
             << "\n"
             << model->getForecastIconCodes()[i]
             << "\n"
             << model->getForecastLongSummary()[i]
             << "\n"
             << model->getForecastShortSummary()[i]
             << "\n"
             << model->getForecastTemperatureSummary()[i]
             << "\n"
             << model->getForecastTemperatureValues()[i]
             << "\n"
             << endl;
    }

    //Second print
    controller->changeLocation(location);
    controller->changeLanguage(language);
    cout << model->getRegion() << "\n"
         << model->getWarning() << "\n" << endl;
    for (int i = 0; i < model->getForecastPeriod().size(); i++)
    {
        cout << model->getForecastPeriod()[i]
             << "\n"
             << model->getForecastIconCodes()[i]
             << "\n"
             << model->getForecastLongSummary()[i]
             << "\n"
             << model->getForecastShortSummary()[i]
             << "\n"
             << model->getForecastTemperatureSummary()[i]
             << "\n"
             << model->getForecastTemperatureValues()[i]
             << "\n"
             << endl;
    }

    delete model;
    delete controller;
    return 0;
}
