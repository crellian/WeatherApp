/**
 * @file MSCUrl.cpp
 * @brief This class provides methods that build syntactically correct urls that are used to located data on an
 * Meteorological Service of Canada (MSC) server.
 *
 */
#include "MSCUrl.h"
using namespace std;

/**
 * @brief Construct a new MSCUrl::MSCUrl object. This constructor builds a search key from the MSC server
 * site list. The search table takes a location and returns its province code and a unique url code. These
 * two codes (and the language specification) are what is required to build a url to locate data on the MSC
 * server. A search table is constructed for each language so that both the french and english names of a
 * location can used to retrieve data for that location.
 *
 */
MSCUrl::MSCUrl()
{
    //Grab the XML page containing the site info
    Connection *web_connection = new Connection("http://dd.weather.gc.ca/citypage_weather/xml/siteList.xml");
    string buffer = web_connection->getPageAsBuffer();

    //Use pugixml parser to build DOM tree from XML document
    pugi::xml_document doc;
    doc.load_buffer_inplace((char *)buffer.c_str(), web_connection->getPageSize());
    //Select nodes from DOM tree using XPATH queries
    pugi::xpath_node_set location = doc.select_nodes("/siteList/site");
    pugi::xpath_node_set location_names_e = doc.select_nodes("/siteList/site/nameEn");
    pugi::xpath_node_set location_names_f = doc.select_nodes("/siteList/site/nameFr");
    pugi::xpath_node_set province_code = doc.select_nodes("/siteList/site/provinceCode");

    //Use the parsed XML data to build key maps containing the necessary location data.
    //Key map takes location name as input and returns an array containing the unique url
    //code for the given location and the province code
    string key_e, key_f;
    array<string, 2> data;
    pair<string, array<string, 2>> to_insert_e, to_insert_f;
    for (int i = 0; i < location.size(); i++)
    {
        key_e = string(location_names_e[i].node().child_value());
        key_f = string(location_names_f[i].node().child_value());
        data[0] = string(location[i].node().attribute("code").value());
        data[1] = string(province_code[i].node().child_value());
        to_insert_e = make_pair(key_e, data);
        to_insert_f = make_pair(key_f, data);

        location_data_e.insert(to_insert_e);
        location_data_f.insert(to_insert_f);
    }
    delete web_connection;
}

/**
 * @brief Destroy the MSCUrl::MSCUrl object
 *
 */
MSCUrl::~MSCUrl()
{
}

/**
 * @brief This method returns the syntactically correct url or for the given location and language using the
 * the search tables built in the constructor
 *
 * @param location Location to retrieve data for
 * @param language Language to retrieve data in
 * @return string Contains the syntactically correct url for the given location and language. If location is
 * not in the search table then it contains the empty string
 */
string MSCUrl::buildUrl(string location, string language)
{
    string url;

    //The given location string will be searched against our list of known locations both french and english names of location are valid
    if (location_data_e.count(location) == 1 || location_data_f.count(location) == 1 )
    {
        //Retrieve the data from the unordered map
        array<string,2> data;
        if (location_data_e.count(location) == 1)
        {
            data = location_data_e[location];
        }
        else
        {
            data = location_data_f[location];
        }
        //Build the url with the information from the unordered_map
        url = "http://dd.weather.gc.ca/citypage_weather/xml/"
            + data[1]  //Contains the province code
            + "/"
            + data[0]  //Contains the unique location code
            + "_"
            + language
            + ".xml";
    }
    else
    {
        //Set url to empty string if given location is not found on the table
        url = "";
    }
    return url;
}
