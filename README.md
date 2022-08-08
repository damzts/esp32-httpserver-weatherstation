# esp32-httpserver-weatherstation
this code and resources for the development of a meteorological http webserver station device using esp32, it uses bme280 temperature sensor, ds1307 RTC to work also
as datalogger, sd card adapter to store readings and its intended to be battery operated with a solar charger controller.

the device is mainly a datalogger saving readings to a csv file, but when a switch is pressed it changes to ap mode in order to host and access to a monitor webpage,
in which you can configure the datalogger parameters such as measuring time, file name and adjust rtc actual time, to keep a precise timestamp, but also explore sd card
content and download the csv file with previous readings.

//specific documentation can be found on my notion webpage only available in spanish.
https://totorres.notion.site/Estaci-n-Meteorol-gica-639292cc71334025ba0a3413dd5eecc8






i want to give credits to KrisKasprzak and G6EJD - David youtube channels to the code provided, the http webserv functions and appereance is based on theirs
but modified, and adding extra function responses for datalogger mode configuration parameters.
https://github.com/G6EJD/ESP32-ESP8266-File-Download-Upload-Delete-Stream-and-Directory
https://github.com/KrisKasprzak/ESP32_WebPage

![alt text](https://github.com/41R-M45T3R/esp32-httpserver-weatherstation/blob/dbe46a4e2241443fc03591eb1c9a7ecf2ec96bc6/base.jpg?raw=true)

![alt text](https://github.com/41R-M45T3R/esp32-httpserver-weatherstation/blob/5f6b85e8efd561f4cf38ee3821db38a5fa890541/webpageold.png?raw=true)





