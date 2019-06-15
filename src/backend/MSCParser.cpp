/**
 * @file MSCParser.cpp
 * @brief This class parses the XML files that are retrived from the Meteorological Service of Canada (MSC) server and stores
 * the data to a Weather struct which the Model can use to populate its fields. Utilizes the open source pugixml xml parser
 * available here https://pugixml.org/
 *
 */
#include "MSCParser.h"
using namespace std;

/**
 * @brief Construct a new MSCParser::MSCParser object
 *
 */
MSCParser::MSCParser() {}

/**
 * @brief Destroy the MSCParser::MSCParser object
 *
 */
MSCParser::~MSCParser() {}

/**
 * @brief This method selectively parses the buffered MSC XML file to populate the fields of a Weather struct
 *
 * @param buffer Contains the MSC XML file
 * @param buffer_size Contains the size of the buffer
 * @return Weather Contains all the relevant data that will be used to populate the Model. See MSCParser.h for
 * declaration of Weather type
 */
Weather MSCParser::parseBuffer(string buffer, size_t buffer_size)
{
    vector<string> v_data_1, v_data_2, v_data_3, v_data_4, v_data_5, v_data_6;

    //Use pugixml parser to build DOM tree from XML document
    pugi::xml_document doc;
    doc.load_buffer_inplace((void *)buffer.c_str(), buffer_size);

    //Select nodes from DOM tree using XPATH queries

    //Name of the forecasting region
    pugi::xpath_node_set data_0 = doc.select_nodes("/siteData/location/region");
    //Warnings/watches/advisories for forecasting region
    pugi::xpath_node_set data_1 = doc.select_nodes("/siteData/warnings/event");
    //Name of the forecast period e.g. Today or Friday
    pugi::xpath_node_set data_2 = doc.select_nodes("/siteData/forecastGroup/forecast/period");
    //Icon codes for the current forecast period
    pugi::xpath_node_set data_3 = doc.select_nodes("/siteData/forecastGroup/forecast/abbreviatedForecast/iconCode");
    //Text summary for the current forecast period
    pugi::xpath_node_set data_4 = doc.select_nodes("/siteData/forecastGroup/forecast/textSummary");
    //Abbreviated text summary for the current forecast period
    pugi::xpath_node_set data_5 = doc.select_nodes("/siteData/forecastGroup/forecast/abbreviatedForecast/textSummary");
    //Text summary of the temperature for the current forecast period
    pugi::xpath_node_set data_6 = doc.select_nodes("/siteData/forecastGroup/forecast/temperatures/textSummary");
    //Numerical temperature values for the current forcast period
    pugi::xpath_node_set data_7 = doc.select_nodes("/siteData/forecastGroup/forecast/temperatures/temperature");

    for(int i=0; i < data_2.size(); i++)
    {
        v_data_1.push_back(string(data_2[i].node().attribute("textForecastName").value()));
        v_data_2.push_back(string(data_3[i].node().child_value()));
        v_data_3.push_back(string(data_4[i].node().child_value()));
        v_data_4.push_back(string(data_5[i].node().child_value()));
        v_data_5.push_back(string(data_6[i].node().child_value()));
        v_data_6.push_back(string(data_7[i].node().child_value()));
    }

    //If there are no warnings set warning to "No Warning" else retrieve the warning
    if(data_1.size() == 0)
    {
        weather_data.warning = "No Warning";
    }
    else
    {
        weather_data.warning = string(data_1.first().node().attribute("description").value());
    }

    weather_data.region = string(data_0.first().node().child_value());
    weather_data.period = v_data_1;
    weather_data.forecast_icon_codes = v_data_2;
    weather_data.forecast_summary_long = v_data_3;
    weather_data.forecast_summary_short = v_data_4;
    weather_data.forecast_temperatures_summary = v_data_5;
    weather_data.forecast_temperatures_value = v_data_6;

    return weather_data;
}
