#ifndef CONNECTION_H
#define CONNECTION_H

/**
 * @file Connection.h
 *
 */
#include <string>
#include "curl/curl.h"

/**
 * @brief This is the declaration of the struct that is passed to the write_callback function.
 * It contains the buffer that stores the contents of the web page and the size of the buffer
 *
 */
struct WebPage
{
    std::string buffer;
    size_t size;
};

class Connection
{
  private:
    WebPage page_info;
    static size_t write_callback(char *, size_t, size_t , void* );

  public:
    Connection(std::string url);
    ~Connection();

    std::string getPageAsBuffer();
    size_t getPageSize();
};

#endif //CONNECTION_H
