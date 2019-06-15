/**
 * @file Connection.cpp
 * @brief This class uses functions from the libcurl library (https://curl.haxx.se/libcurl/) to retrieve a web page
 * from the given URL and store it in a buffer
 *
 */
#include "Connection.h"
using namespace std;

/**
 * @brief Construct a new Connection:: Connection objec. All the networking is done in this constructor. The moment
 * an instantiation has been created the web page has been stored to memory
 *
 * @param url The url that the web page will be retrieved from
 */
Connection::Connection(string url)
{
    //Initialize the WebPage fields
    page_info.buffer = "";
    page_info.size = 0;

    CURL *curl_handle;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    curl_handle = curl_easy_init();
    //Set the url
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    //Set the function that will be called to write the page contents
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
    //Ensure data is written to page_info using write function
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *) &page_info);
    //Retrieve the web page
    res = curl_easy_perform(curl_handle);

    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();
}

/**
 * @brief Destroy the Connection:: Connection object
 *
 */
Connection::~Connection()
{
}

/**
 * @brief Returns the web page as a buffer
 *
 * @return string Contains the entire web page located at the given url
 */
string Connection::getPageAsBuffer()
{
    return page_info.buffer;
}

/**
 * @brief Returns the size of the web page in bytes
 *
 * @return size_t size of the retrieved web page in bytes
 */
size_t Connection::getPageSize()
{
    return page_info.size;
}

/**
 * @brief Helper function utilized by libcurl functions. Mandatory if data is to be written to a buffer.
 * Note that this function is called many times while the web page is being fetched
 *
 * @param page_contents The current page contents that have be retrieved so far
 * @param size Size of each character in the page_contents array
 * @param nmemb Size of the page contents array
 * @param input_struct Contains the fields that store the page contents and the page size
 * @return size_t Returns the total size of the retrieved page in bytes
 */
size_t Connection::write_callback(char *page_contents, size_t size, size_t nmemb, void *input_struct)
{
    size_t realsize = size * nmemb;
    WebPage *input_struct_cast = (WebPage *)input_struct;
    //Build the buffer with each call of the function
    input_struct_cast->buffer += string(page_contents);
    //Record the cumulative size of the buffer
    input_struct_cast->size += realsize;

    return realsize;
}
