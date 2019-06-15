#ifndef CONTROLLER_H
#define CONTROLLER_H
/**
 * @file Controller.h
 *
 */
#include <string>
#include "Model.h"
#include "MSCUrl.h"

class Controller
{
  private:
    MSCUrl * url_builder;
    std::string current_location;
    std::string current_language;
    std::string current_source;
    Model* model;


  public:
    Controller(Model* model);
    ~Controller();

    void checkForUpdates();
    void changeLanguage(std::string language);
    int changeLocation(std::string location);
};

#endif //CONTROLLER_H
