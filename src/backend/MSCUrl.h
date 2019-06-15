#ifndef MSCURL_H
#define MSCURL_H
/**
 * @file MSCUrl.h
 *
 */
#include <string>
#include <unordered_map>
#include <array>
#include "pugixml-1.9/pugixml.hpp"
#include "Connection.h"

class MSCUrl
{
private:
  //unordered_map (hash map) takes location name as input and returns array containing the unique url code
  //and the province code for the location. There is a hash map for each language, allowing for both french
  //and english location queries
  std::unordered_map<std::string, std::array<std::string, 2>> location_data_e;
  std::unordered_map<std::string, std::array<std::string, 2>> location_data_f;

public:
  MSCUrl();
  ~MSCUrl();

  std::string buildUrl(std::string, std::string);
};

#endif //MSCURL_H
