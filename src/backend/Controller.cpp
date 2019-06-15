/**
 * @file Controller.cpp
 * @brief This class is the serves as the input interface for the View. If any data is to be changed in the Model
 * then it is done through the methods in this class. Defaults can be set in the constructor
 *
 */
#include "Controller.h"
using namespace std;

/**
 * @brief Construct a new Controller:: Controller object. This constructor sets the default location and language and
 * since we know that we will be retrieving data from a Meteorological Service of Canada (MSC) server instantiates
 * then we instanciate an MSCUrl to build urls from the given language and location
 *
 * @param model
 */
Controller::Controller(Model *model)
{
    url_builder = new MSCUrl();

    this->model = model;
    //SET DEFAULTS
    //London Ontario is the default location
    current_location = "London";
    //English is the default language
    current_language = "e";
    //London url for MSC server
    current_source = url_builder->buildUrl(current_location, current_language);
}

/**
 * @brief Destroy the Controller:: Controller object. It should be noted that creating a MSCUrl is
 * an expensive process in terms of time hence it is done once in this class and is deleted when
 * this class is deleted. See MSCUrl.cpp for more details
 *
 */
Controller::~Controller()
{
    delete url_builder;
}

/**
 * @brief This method updates all the data available in the Model. It should be called periodically
 * in order to ensure the data available in the Model remains as current as possible
 *
 */
void Controller::checkForUpdates()
{
    model->updateData(current_source);
}

/**
 * @brief This method changes the forecasting location of the data in the Model e.g entering
 * "London" would return forecasting data for London, Ontario. If the input name is found on
 * this site list http://dd.weather.gc.ca/citypage_weather/xml/siteList.xml then the Model will
 * be updated assuming spelling (case sensitive) is exact.
 *
 * @param location The location that the data will be retrieved for
 * @return int Returns 1 is the given location was valid, otherwise it returns 0
 */
int Controller::changeLocation(string location)
{
    //Build a new url for the given location and current language
    string source = url_builder->buildUrl(location, current_language);

    if (source.empty())
    {
        return 0;
    }
    else
    {
        //Since the location change is valid the current_source and current_location are updated
        current_source = source;
        current_location = location;

        //Update the model with data from the updated source
        model->updateData(current_source);

        return 1;
    }
}

/**
 * @brief This method changes the language of the data available in the Model from either French or English.
 * Since the user is only ever given two options to chose from then we know that any input will be correct.
 *
 * @param language Options are strings "e" and "f" for english and french, respectively
 */
void Controller::changeLanguage(string language)
{
    string source = url_builder->buildUrl(current_location, language);

    //Since a language change is always valid current_source, current_language and current_location_key can be updated immediately
    current_source = source;
    current_language = language;

    //Update the model with data from the updated source
    model->updateData(current_source);
}
