Welcome to our project readme.

To run our app navigate to the 'bin' folder and simply run the WEATHERAPP executable from the command line. You can test the backend code 
by running the TEST executable. Refer to test.cpp to understand what TEST is printing to the screen and how to change it.

To build this project from source a couple prerequisites are required. First, our project utilizes QT for the frontend GUI so your system 
must have some QT dependencies downloaded. Assuming your are on a Debian like system (as is the case with the Raspberry Pi) then the 
following commands in terminal should do it:

sudo apt-get install build-essential libgl1-mesa-dev
sudo apt-get install qtdeclarative5-dev

Please make sure that the following versions are correct:

qmake 3.0
qt 5.7.1

Second, to enable the networking done in the backend, libcurl (https://curl.haxx.se/libcurl/) is required. The following command in the 
terminal should download it:

sudo apt-get install libcurl4-openssl-dev

Now you are ready to build our project from source. Navigate to the 'src' folder and type the following to build:

qmake WEATHERAPP
qmake
make

The WEATHERAPP executable should now be found in the 'src' folder and can be run if ./WEATHERAPP is typed to the command line.

To build the test file from source navigate to the 'backend' folder within the 'src' folder. Typing 'make' to the command line
will build an executable named 'Test' in the 'backend' folder. 

It should also be noted that the backend code relies on the open source software pugixml (https://pugixml.org/) to parse the xml
files that are retrieved from our data source - which is the Meteorological Service of Canada (MSC) server, see here 
http://dd.weather.gc.ca/about_dd_apropos.txt for more details - pugixml is shipped with our project and can be found in the 
'pugixml-1.9' folder within the 'backend' folder. 

