#ifndef MSCPARSER_H
#define MSCPARSER_H
/**
 * @file MSCParser.h
 *
 */
#include <string>
#include <vector>
#include "pugixml-1.9/pugixml.hpp"

/**
 * @brief This is the struct that the parsed data will be written to and what the
 * Model uses to update its fields
 *
 */
struct Weather
{
    std::string region;
    std::string warning;
    std::vector<std::string> period;
    std::vector<std::string> forecast_icon_codes;
    std::vector<std::string> forecast_summary_long;
    std::vector<std::string> forecast_summary_short;
    std::vector<std::string> forecast_temperatures_summary;
    std::vector<std::string> forecast_temperatures_value;
};

class MSCParser
{
  private:
    Weather weather_data;

  public:
    MSCParser();
    ~MSCParser();

    Weather parseBuffer(std::string buffer, size_t buffer_size);
};

#endif //MSCPARSER_H
