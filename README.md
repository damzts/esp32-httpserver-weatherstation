# esp32-httpserver-weatherstation
this code and resources for the development of a meteorological http webserver station device using esp32, it uses bme280 temperature sensor, ds1307 RTC to work also
as datalogger, sd card adapter to store readings and its intended to be battery operated with a solar charger controller.

the device is mainly a datalogger saving readings to a csv file, but when a switch is pressed it changes to ap mode in order to host and access to a monitor webpage,
in which you can configure the datalogger parameters such as measuring time, file name and adjust rtc actual time, to keep a precise timestamp, but also explore sd card
content and download the csv file with previous readings.

i want to give credits to KrisKasprzak and G6EJD - David youtube channels to the code provided, the http webserv functions and appereance is based on theirs
but modified, and adding extra function responses for datalogger mode configuration parameters.
https://github.com/G6EJD/ESP32-ESP8266-File-Download-Upload-Delete-Stream-and-Directory
https://github.com/KrisKasprzak/ESP32_WebPage

![alt text]([https://github.com/[username]/[reponame]/blob/[branch]/image.jpg](https://github.com/41R-M45T3R/esp32-httpserver-weatherstation/blob/e52358e81cc5d83970b2d3541e2052e2bb6a2547/base.jpg)?raw=true)
