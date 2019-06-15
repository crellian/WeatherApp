/**
 * @file Model.cpp
 * @brief This class presents all the data that the View would require. Any changes to the data in the
 * Model are done through the Controller via the updataData() method.
 *
 */
#include "Model.h"
using namespace std;

/**
 * @brief Construct a new Model:: Model object
 *
 */
Model::Model() {}

/**
 * @brief Destroy the Model:: Model object
 *
 */
Model::~Model() {}

/**
 * @brief Updates the data in the Model using the web page located at the URL contained in "source".
 * Since we know the data is coming from a Meteorological Service of Canada (MSC) server we use an
 * MSCParser to parse it and fill the Model
 *
 * @param source Contains the URL which locates the data that will be used to fill the Model
 */
void Model::updateData(string source)
{
    Connection *web_connection = new Connection(source);
    MSCParser *parser = new MSCParser();
    Weather weather_data = parser->parseBuffer(web_connection->getPageAsBuffer(), web_connection->getPageSize());

    region = weather_data.region;
    warning = weather_data.warning;
    forecast_icon_codes = weather_data.forecast_icon_codes;
    period = weather_data.period;
    forecast_summary_short = weather_data.forecast_summary_short;
    forecast_summary_long = weather_data.forecast_summary_long;
    forecast_temperatures_summary = weather_data.forecast_temperatures_summary;
    forecast_temperatures_value = weather_data.forecast_temperatures_value;

    delete parser;
    delete web_connection;
}

/**
 * @brief Returns the forecasting region for the weather data in the rest of the Model
 *
 * @return string Contains the name(s) of the current forecasting region
 */
string Model::getRegion()
{
    return region;
}

/**
 * @brief Returns any warnings/watches/advisories for the current forecasting region. If no
 * special weather statement has been issued then "No Warning" is returned
 *
 * @return string Contains warnings/watches/advisories statements
 */
string Model::getWarning()
{
    return warning;
}

/**
 * @brief Returns the forecast period by day e.g Today , Tonight , Monday , Monday Night, etc...
 * Length of the vector varies between 12 and 13 based on the current time of day
 *
 * @return vector<string> Contains name of the day for each day in the forecasting period
 */
vector<string> Model::getForecastPeriod()
{
    return period;
}

/**
 * @brief Returns the unique icon code for the forecast conditions. This link downloads a csv file that provides the weather condtion
 * associated with a given icon code:
 * http://dd.weather.gc.ca/citypage_weather/docs/current_conditions_icon_code_descriptions_e.csv
 * And this link redirects to a pdf containing pictoral representations of the weather conditions:
 * http://dd.weather.gc.ca/citypage_weather/docs/Current_Conditions_Icons-Icones_conditions_actuelles.pdf
 * e.g and icon code of 00 corresponds to a sunny day. These codes are meant to be used to decide on what picture should be shown
 * for the given condition as they are unique.
 *
 * @return vector<string> Contains icon codes for each day in the forecasting period
 */
vector<string> Model::getForecastIconCodes()
{
    return forecast_icon_codes;
}

/**
 * @brief Returns a long text summary of the weather conditions for each day in the forecasting period
 *
 * @return vector<string> Contains long weather summaries for each day in the forecating period
 */
vector<string> Model::getForecastLongSummary()
{
    return forecast_summary_long;
}

/**
 * @brief Returns an abbreviated text summary of the weather conditions for each day in the forecasting period
 *
 * @return vector<string> Contains shorter weather summaries for each day in the forecating period
 */
vector<string> Model::getForecastShortSummary()
{
    return forecast_summary_short;
}

/**
 * @brief Returns a text summary of the temperature for each day in the forecasting period
 *
 * @return vector<string> Contains text summaries of the temperature for each day in the forecast
 */
vector<string> Model::getForecastTemperatureSummary()
{
    return forecast_temperatures_summary;
}

/**
 * @brief Returns the numeric temperature value for each day in the forecast
 *
 * @return vector<string> Contains the numeric temperature value for each day in the forecast
 */
vector<string> Model::getForecastTemperatureValues()
{
    return forecast_temperatures_value;
}
