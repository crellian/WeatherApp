#ifndef MODEL_H
#define MODEL_H
/**
 * @file Model.h
 *
 */
#include <string>
#include <vector>
#include "Connection.h"
#include "MSCParser.h"

class Model
{
private:
  std::string region;
  std::string warning;
  std::vector<std::string> period;
  std::vector<std::string> forecast_icon_codes;
  std::vector<std::string> forecast_summary_long;
  std::vector<std::string> forecast_summary_short;
  std::vector<std::string> forecast_temperatures_summary;
  std::vector<std::string> forecast_temperatures_value;

public:
  Model();
  ~Model();

  void updateData(std::string);
  std::string getRegion();
  std::string getWarning();
  std::vector<std::string> getForecastPeriod();
  std::vector<std::string> getForecastIconCodes();
  std::vector<std::string> getForecastLongSummary();
  std::vector<std::string> getForecastShortSummary();
  std::vector<std::string> getForecastTemperatureSummary();
  std::vector<std::string> getForecastTemperatureValues();
};

#endif //MODEL_H
