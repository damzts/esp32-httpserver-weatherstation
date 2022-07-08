//======================================================================
//ESP32 Weather Station: DataLogger & WifiAP http webserver using AJAX
//======================================================================

//================ wifi libraries =================================
#include <WiFi.h> 
#include <WiFiClient.h>
#include <WebServer.h>
#include "webpage.h"
//================ bme280 libraries setup =========================
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
//bme280 I2C link (used)
Adafruit_BME280 bme;
//================ I2C RTC Adress ================================
//definir la direccion i2c del rtc ds1307
#define DS3231_I2C_ADDRESS 0x68
//================ SD MMC libraries ==============================
#include "FS.h"
#include "SD_MMC.h"
bool  SD_present = false;
//================ general purpose variables =====================
String dayStamp;
String timeStamp;
float temperature,pressure,humidity,height;
String dataMessage;
uint32_t SensorUpdate = 0;
String webpage = "";
char webpageinput[1024];
float batteryLevel;
//================ deep sleep variables ==========================
unsigned int uSfactor = 1000000; // Conversion factor for seconds to micro seconds
int processTime=0;
RTC_DATA_ATTR int readingID = 0;// Save reading number on RTC memory
//================ nvs variables ================================= non volatile storage
#include <Preferences.h>
String csvtitle; //"undefined location"
String archivoactivo;
int timesleep; // in seconds
Preferences preferences;
//================= wifi AP configurations =======================
// here you post web pages to your homes intranet which will make page debugging easier
//#define USE_INTRANET
// replace this with your homes intranet connect parameters
#define LOCAL_SSID "INFINITUMED79"
#define LOCAL_PASS "3446117178"
// once  you are read to go live these settings are what you client will connect to
#define AP_SSID "TestWebSite"
#define AP_PASS "023456789"
// the XML array size needs to be bigger that your maximum expected size. 2048 is way too big for this example
char XML[256];
// just some buffer holder for char operations
char buf[256];
char buf2[256];
// variable for the IP reported when you connect to your homes intranet (during debug mode)
IPAddress Actual_IP;
// definitions of your desired intranet created by the ESP32
IPAddress PageIP(1,1,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress ip;
// Set web server port number to 80
WebServer server(80);

//======================================================================
//                            setup
//======================================================================
void setup() {
  


  //SD MMC input pullups
  pinMode(2,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  pinMode(13,INPUT_PULLUP);
  pinMode(15,INPUT_PULLUP);


  //WiFi LED
  pinMode(32,OUTPUT);
  //Interrupt pin
  pinMode(33,INPUT_PULLUP);
  //Batery Monitor
  pinMode(34,INPUT);

  Serial.begin(115200);
  Wire.begin();

  //nvs namespace
  preferences.begin("databackup",false);

  //================= detectar e iniciar bme280 ==================
  Serial.println("BME280 test.........");
  bool status;
  // bme280 default I2C address 76
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  Serial.println("-- BME280 is OK! --");
  
//================= detectar e iniciar SD MMC ===================
  if(!SD_MMC.begin("/sdcard",false)){
    SD_present = false; 
    while(!SD_present){
      Serial.println("Card Mount Failed");
      Serial.println();
      SD_present = SD_MMC.begin("/sdcard",false);
    }
    if(SD_present == true){ESP.restart();}
  }
  SD_present = true;
  uint8_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE){
      Serial.println("No SD_MMC card attached,use other card");
      SD_present = false;
      while (1);
  }
//================= check nvs for csv title & sleeptime ========
csvtitle = preferences.getString("csvtitle","undefined location");
timesleep = preferences.getInt("timesleep",1);
archivoactivo = preferences.getString("filename","data.csv");
Serial.println(csvtitle);
Serial.println(timesleep);
Serial.println(archivoactivo);
preferences.end();
//================= detectar el archivo y dar formato ==========
  // If the data.txt file doesn't exist, create a file on the SD card and write the data labels
  File file = SD_MMC.open("/"+archivoactivo); //SD_MMC.open("/data.csv");
  if(!file) {
    Serial.println("File doens't exist");
    Serial.println("Creating file...");
    strcpy(buf,"");
    strcpy(buf2,"");
    sprintf(buf,"%s\r\nID,Fecha,Hora,Temperatura_C,Humedad_%%,Presion_hPa,\r\n",csvtitle.c_str());
    sprintf(buf2,"/%s",archivoactivo.c_str());
    writeFile(SD_MMC,buf2, buf);
    readingID = 0;
  }else {
    Serial.println("File already exists");
    float megabytes = file.size()/1024.0/1024.0;
    if (megabytes < 4095.0){
      Serial.print("Filesize: "); Serial.println(megabytes); 
    }else{
      //open
      preferences.begin("databackup",false);
      //put
      preferences.putString("filename","1"+archivoactivo);
      //close
      preferences.end();
      ESP.restart();
    }
  }
  file.close();
//================= enable ext0 interrupt ==============================
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,0);

  
  if(digitalRead(33) == LOW ){
//======================================================================
//                    WIFI PROCESS
//======================================================================
    Serial.println("Trigger Wifi Recibido");
    // Connect to Wi-Fi network with SSID and password
    Serial.print("Starting Server");
    
    //================= Intranet Process  ====================
    // if you have this #define USE_INTRANET,  you will connect to your home intranet, again makes debugging easier
    #ifdef USE_INTRANET
      WiFi.begin(LOCAL_SSID, LOCAL_PASS);
        while (WiFi.status() != WL_CONNECTED) {
          delay(250);
          Serial.print(".");
        }
      Serial.print("Intranet IP address: "); Serial.println(WiFi.localIP());
      Actual_IP = WiFi.localIP();
    #endif
    
    //================= AP Mode Process  ====================
    // if you don't have #define USE_INTRANET, here's where you will creat and access point
    // an intranet with no internet connection. But Clients can connect to your intranet and see
    // the web page you are about to serve up
    #ifndef USE_INTRANET
      WiFi.softAP(AP_SSID, AP_PASS);
      delay(100);
      WiFi.softAPConfig(PageIP, gateway, subnet);
      delay(100);
      Actual_IP = WiFi.softAPIP();
      Serial.print("IP address: "); Serial.println(Actual_IP);
    #endif
    
    //================= page responses  ====================
    server.on("/", homepage);
    server.on("/dir",SD_dir);
    server.on("/download",File_Download);
    server.on("/delete",File_Delete);
    server.on("/stream",File_Stream);
    server.on("/config",Config);
    //================= internal config response ===========
    server.on("/syncdatetime",  sync_datetime);
    server.on("/updtitle",  updatecsvtitle);
    server.on("/updtime", updatesleeptime);
    server.on("/newfile", runnewfile);
    server.on("/titledisplay", titledisplay);
    server.on("/sleeptimedisplay", sleeptimedisplay);
    server.on("/activefiledisplay", activefiledisplay);
    //upon esp getting /XML string, ESP will build and send the XML, this is how we refresh just parts of the web page
    server.on("/xml", SendXML);
    //================= server begin  =======================
    server.begin();
    Serial.println("HTTP server started");
    //turn on LED
    digitalWrite(32,HIGH);
  }else{
//======================================================================
//                    OFFLINE PROCESS
//======================================================================
    // Get values
    getReadings();  // from the bme280
    getTimeStamp(); // from the ds1307
    logSDCard();
    readingID++;  // Increment readingID on every new reading

    //================= prepare to deep sleep  ===============
    //restar el tiempo que lleva encendido al tiempo de sueño y validar que no duerma <= 0 segundos
    processTime = micros();//micros() - timeold ; // time in microseconds
    Serial.println(processTime*1000000);
    if(processTime>(timesleep * uSfactor)){
      processTime=0;
    }
    // Enable Timer wake_up 
    esp_sleep_enable_timer_wakeup((timesleep * uSfactor) - processTime); // tiempo para dormir y restale el tiempo de proceso para ajustar bien el muestreo
    // Start deep sleep
    Serial.println("DONE! Going to sleep now... : ");
    esp_deep_sleep_start();
  }
}
//======================================================================
//                          loop
//======================================================================
void loop() { 
  //================= escape wifi mode  ===============
  if(digitalRead(33) != LOW){
    digitalWrite(32,LOW);
    esp_sleep_enable_timer_wakeup(1 * uSfactor);
    Serial.println("DONE! Going to sleep now... : ");
    readingID = 0;
    esp_deep_sleep_start();
  }

  

  

 //================= refresh sensor values  =========== && rtc ds1307 date & time stamps variables
  if ((millis() - SensorUpdate) >= 500) {
    //Serial.println("Reading Sensors");
    SensorUpdate = millis();
    getReadings();
    getTimeStamp();
    batteryLevel = map(analogRead(34), 0.0f, 4095.0f, 0, 100);
    //Serial.println(batteryLevel);
    
  }

   //================= webserver handle  =============
  // no matter what you must call this handleClient repeatidly--otherwise the web page
  // will not get instructions to do something
  server.handleClient(); delay(1);
}

//======================================================================
//                    Functions
//======================================================================

//================= get sensor readings  ===============
void getReadings() {
  //Serial.println("Getting readings... ");

  temperature = bme.readTemperature();
  // Convert temperature to Fahrenheit
  /*Serial.print("Temperature = "); Serial.print(1.8 * bme.readTemperature() + 32); Serial.println(" *F");*/
  humidity =  bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
  //height = bme.readAltitude(SEALEVELPRESSURE_HPA);

  //Serial.print("Humidity = "); Serial.print(humidity); Serial.println(" %");
  //Serial.print("Temperature = "); Serial.print(temperature); Serial.println(" °C");
  //Serial.print("Pressure = "); Serial.print(pressure); Serial.println(" hPa");
  //Serial.print("Approx. Altitude = "); Serial.print(height); Serial.println(" m");
  
}
//================= get RTC timeStamp  =================
void getTimeStamp(){
  
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

  timeStamp = String(hour) + ":";
  
  if (minute<10){
  timeStamp +=  "0";
  }
  timeStamp += String(minute) + ":";
  
  if (second<10){
  timeStamp +=  "0";
  }
  timeStamp += String(second);
  
  dayStamp = String(dayOfMonth)+ "/" + String(month) + "/" + String(year);
  //Serial.println(dayStamp);
  //Serial.println(timeStamp);
  
}
//================= save readings to SD MMC  ===========
void logSDCard() {
  dataMessage = String(readingID) + "," + String(dayStamp) + "," + String(timeStamp) + "," + 
                String(temperature) + "," + String(humidity) + "," + String(pressure)+ "\r\n";
  Serial.print("Save data: ");
  Serial.println(dataMessage);
  strcpy(buf2,"");
  sprintf(buf2,"/%s",archivoactivo.c_str());
  appendFile(SD_MMC,buf2, dataMessage.c_str());
}
//======================================================================
//                  RTC functions
//======================================================================
byte decToBcd(byte val){
  return( (val/10*16) + (val%10) );
  // Convert normal decimal numbers to binary coded decimal
}                                                 
byte bcdToDec(byte val){
  return( (val/16*10) + (val%16) );
  // Convert binary coded decimal to normal decimal numbers
}
//================= Set RTC Time Values  ===============                                     
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year){
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
//================= Get RTC Time Values  ===============
void readDS3231time(byte *second,byte *minute,byte *hour,byte *dayOfWeek,byte *dayOfMonth,byte *month,byte *year){
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
//======================================================================
//                    SD MMC WRITE & APPEND (DON'T MODIFY)
//======================================================================
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}
//======================================================================
//                    HTTP handle functions
//======================================================================
void homepage(){ 
  SendHTML_Header();
  //body webpage+=
  webpage=String(homebody);
  //send second half
  webpage+=String(htmlFooter);
  server.sendContent(webpage);
  webpage="";
  //stop
  server.sendContent("");
  server.client().stop(); // Stop is needed because no content length was sent
}
//========================================================
void SendHTML_Header(){
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate"); 
  server.sendHeader("Pragma", "no-cache"); 
  server.sendHeader("Expires", "-1"); 
  server.setContentLength(CONTENT_LENGTH_UNKNOWN); 
  server.send(200, "text/html","");
  webpage=String(htmlHeader);
  server.sendContent(webpage);
  webpage="";
}
//========================================================
void File_Download(){ // This gets called twice, the first pass selects the input, the second pass then processes the command line arguments
  if (server.args() > 0 ) { // Arguments were received
    if (server.hasArg("download")) DownloadFile(server.arg(0));
  }
  else SelectInput("Escribe el nombre del archivo a Descargar","download","download");
}
//========================================================
void DownloadFile(String filename){
  if (SD_present) { 
    File download = SD_MMC.open("/"+filename);
    if (download) {
      server.sendHeader("Content-Type", "text/text");
      server.sendHeader("Content-Disposition", "attachment; filename="+filename);
      server.sendHeader("Connection", "close");
      server.streamFile(download, "application/octet-stream");
      download.close();
    } //else ReportFileNotPresent("download"); 
  } //else ReportSPIFFSNotPresent();
}
//========================================================
void File_Delete(){
  if (server.args() > 0 ) { // Arguments were received
    if (server.hasArg("delete")) DeleteFile(server.arg(0));
  }
  else SelectInput("Escribe el nombre del archivo a Eliminar","delete","delete");
}
//========================================================
void DeleteFile(String filename) { // Delete the file 
  if (SD_present) { 
    SendHTML_Header();
    webpage +="<div class='category'> </div>";
    
    File dataFile = SD_MMC.open("/"+filename, "r"); // Now read data from SD Card 
    if (dataFile){
      if (SD_MMC.remove("/"+filename)){
        //Serial.println(F("File deleted successfully"));
        webpage += "<h3>El archivo '"+filename+"' se ha eliminado correctamente</h3>"; 
        webpage += F("<a href='/delete'>[Regresar]</a><br><br>");
      }else{ 
        webpage += F("<h3>No se ha podido eliminar el archivo - ERROR!</h3>");
        webpage += F("<a href='delete'>[Regresar]</a><br><br>");
      }
    } //else ReportFileNotPresent("delete");
    
    //send second half
    webpage += String(htmlFooter);
    server.sendContent(webpage);
    webpage="";
    //stop
    server.sendContent("");
    server.client().stop(); // Stop is needed because no content length was sent
  } //else ReportSPIFFSNotPresent();
}
//========================================================
void File_Stream(){
  if (server.args() > 0 ) { // Arguments were received
    if (server.hasArg("stream")) streamFile(server.arg(0));
  }
  else SelectInput("Escribe el nombre del archivo a Desplegar","stream","stream");
}
//---------------------------------------
void streamFile(String filename) { 
  if (SD_present) { 
    File dataFile = SD_MMC.open("/"+filename, FILE_READ); // Now read data from SPIFFS Card 
    if (dataFile) { 
      if (dataFile.available()) { // If data is available and present 
        String dataType = "text/plain"; //"application/octet-stream"; 
        if (server.streamFile(dataFile, dataType) != dataFile.size()) {Serial.print(F("Sent less data than expected!")); } 
      }
      dataFile.close(); // close the file: 
    } //else ReportFileNotPresent("Cstream");
  } //else ReportSPIFFSNotPresent(); 
}   
//========================================================
void SelectInput(String heading1, String command, String arg_calling_name){
  SendHTML_Header();
  //body
  strcpy(buf,"");
  sprintf(buf,"<div class='category'>%s</div><div class='heading' style='margin:0 auto;'>%s</div><form class='card' style='width:50%%; margin: 0 auto;' action='/%s' method='post'><div class='input-group'>",command,heading1.c_str(),command);
  strcat(webpageinput,buf);
  sprintf(buf,"<input type='text' class='form-control' placeholder='nombre + .csv' name='%s' value=''>",arg_calling_name);
  strcat(webpageinput,buf);
  sprintf(buf,"<button type='submit' class='btn-secondary'>Enter</button></div></form> <a class='bodytext' href='/'>[Regresar]</a>",arg_calling_name);
  strcat(webpageinput,buf);
  webpage=String(webpageinput);
  strcpy(webpageinput,"");
  
  //send second half
  webpage+=String(htmlFooter);
  server.sendContent(webpage);
  webpage="";
  //stop
  server.sendContent("");
  server.client().stop(); // Stop is needed because no content length was sent
}
//========================================================
void SD_dir(){ 
  if (SD_present) { 
    File root = SD_MMC.open("/");
    if (root) {
      root.rewindDirectory();
      SendHTML_Header();
      webpage=String(dirbody);
      printDirectory("/",0);
      webpage += F("</table>");
      server.sendContent(webpage);
      webpage="";
      root.close();
    }
    else 
    {
      SendHTML_Header();
      webpage += F("<h3>No se encontraron archivos!</h3>");
    }
  //send second half
  webpage+=String(htmlFooter);
  server.sendContent(webpage);
  webpage="";
  //stop
  server.sendContent("");
  server.client().stop(); // Stop is needed because no content length was sent
  }
}
//========================================================
void printDirectory(const char * dirname, uint8_t levels){
  
  File root = SD_MMC.open(dirname);
  if(!root){
    return;
  }
  if(!root.isDirectory()){
    return;
  }
  File file = root.openNextFile();
  while(file){
    if (webpage.length() > 1000) {
      server.sendContent(webpage);
      webpage="";
    }
    if(file.isDirectory()){
      webpage += "<tr><td><div class='bodytext'>"+String(file.isDirectory()?"Dir":"Archivo")+"</div></td><td><div class='tabledata'>"+String(file.name())+"</div></td><td></td><td></td></tr>";
      printDirectory(file.name(), levels-1);
    }
    else
    {
      webpage += "<tr><td><div class='bodytext'>"+String(file.name())+"</div></td>";
      webpage += "<td><div class='tabledata'>"+String(file.isDirectory()?"Dir":"Archivo")+"</div></td>";
      int bytes = file.size();
      String fsize = "";
      if (bytes < 1024)                     fsize = String(bytes)+" B";
      else if(bytes < (1024 * 1024))        fsize = String(bytes/1024.0,3)+" KB";
      else if(bytes < (1024 * 1024 * 1024)) fsize = String(bytes/1024.0/1024.0,3)+" MB";
      else                                  fsize = String(bytes/1024.0/1024.0/1024.0,3)+" GB";
      webpage += "<td><div class='tabledata'>"+fsize+"</div></td>";
      webpage += "<td><form action='/download' method='post'><div class='input-group'><button style='width:100%; margin: 0 auto;' type='submit' class='btn-secondary' name='download' value='"+String(file.name())+"'>Descarga</button></div></form></td></tr>";
      
    }
    file = root.openNextFile();
  }
  file.close();
}
//========================================================
void Config(){
    SendHTML_Header();
    //body
    webpage=String(confbody);
    //send second half
    webpage+=String(htmlFooter);
    server.sendContent(webpage);
    webpage="";
    //stop
    server.sendContent("");
    server.client().stop(); // Stop is needed because no content length was sent
}
//========================================================
void sync_datetime(){

   uint8_t weekdayIndex;
   int dayMonth;
   int month;
   int year;
   int hour;
   int minute;
   int second;
   int dayofweek;
   
   const char *weekdayName[] = {
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
  "Saturday"};

  String t1 = server.arg("VALUE");
  String t2 = server.arg("VALUE2");
  String t3 = server.arg("VALUE3");

  const char *t_state=t1.c_str();
  const char *t_state2=t2.c_str();
  const char *t_state3=t3.c_str();

  //convert payload
  //dd/mm/yyyy
  //Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday
  //hh:mm:ss 

  //separate dd/mm/yyyy to dayMonth, month, year
  if (sscanf(t_state, "%d/%d/%d", &dayMonth, &month, &year) != 3) {
    Serial.println("error on date formating");
  }
  year=year-1900;
  year=year%100;

  // Convert weekday string to weekday number
  for (weekdayIndex = 0; weekdayIndex < 7; weekdayIndex++) {
      if (strcmp(t_state2, weekdayName[weekdayIndex]) == 0) {
          break;
      }
  }
  
  if (weekdayIndex >= 7) {
      // Not found
      Serial.println("error on index weekday >7");
  }
  dayofweek=weekdayIndex+1;

  //separate hh/mm/ss to hour, minute, second
  if (sscanf(t_state3, "%d:%d:%d", &hour, &minute, &second) != 3) {
    Serial.println("error on time formating");
  }

  //------------ funcion para ajustar el tiempo del RTC 
  // set the initial time here:
  // DS3231 seconds, minutes, hours, day, date, month, year
  //setDS3231time(0,55,3,1,10,4,22);
  setDS3231time(second,minute,hour,dayofweek,dayMonth,month,year);
  
  /* debug only purpose
  Serial.print("DATE UPDATED: "); Serial.println(t_state);
  Serial.print("WEEKDAY UPDATED: "); Serial.println(t_state2);
  Serial.print("TIME UPDATED: "); Serial.println(t_state3);

  Serial.print("sec: "); Serial.println(second);
  Serial.print("min: "); Serial.println(minute);
  Serial.print("hr: "); Serial.println(hour);
  Serial.print("dayofweek: "); Serial.println(dayofweek);
  Serial.print("date: "); Serial.println(dayMonth);
  Serial.print("month: "); Serial.println(month);
  Serial.print("year: "); Serial.println(year);
  */
  
  strcpy(buf,"Actualizado!");
  server.send(200, "text/plain", buf); //Send web page
}
//========================================================
void updatecsvtitle(){
  String csvtitletext = server.arg("VALUE");
  //open
  preferences.begin("databackup",false);
  //put
  preferences.putString("csvtitle", csvtitletext);
  //close
  preferences.end();
  //response
  strcpy(buf,"Informacion Actualizada!");
  server.send(200, "text/plain", buf); //Send web page
}
//========================================================
void updatesleeptime(){
  String sleeptimetext = server.arg("VALUE");
  //string to int
  int sleeptimeInt;
  sleeptimeInt=sleeptimetext.toInt();
  //open
  preferences.begin("databackup",false);
  //put
  preferences.putInt("timesleep", sleeptimeInt);
  //close
  preferences.end();
  //response
  strcpy(buf,"Informacion Actualizada!");
  server.send(200, "text/plain", buf); //Send web page
}
//========================================================
void runnewfile(){
  String newfilename = server.arg("VALUE");
  //open
  preferences.begin("databackup",false);
  //put
  preferences.putString("filename", newfilename);
  //close
  preferences.end();
  //response
  strcpy(buf,"Nuevo archivo activo!");
  server.send(200, "text/plain", buf); //Send web page
}
//========================================================
void titledisplay(){
  //open
  preferences.begin("databackup",false);
  //put
  csvtitle = preferences.getString("csvtitle","undefined location");
  //close
  preferences.end();
  //response
  sprintf(buf,"Titulo Actual: %s",csvtitle.c_str());
  server.send(200, "text/plain", buf); //Send web page
}
//========================================================
void sleeptimedisplay(){
  //open
  preferences.begin("databackup",false);
  //put
  timesleep = preferences.getInt("timesleep",1);
  //close
  preferences.end();
  //response
  sprintf(buf,"Muestreo Actual: %s",String(timesleep));
  server.send(200, "text/plain", buf); //Send web page
}
//========================================================
void activefiledisplay(){
  //open
  preferences.begin("databackup",false);
  //put
  archivoactivo = preferences.getString("filename","data.csv");
  //close
  preferences.end();
  //response
  sprintf(buf,"Archivo Activo: %s",archivoactivo.c_str());
  server.send(200, "text/plain", buf); //Send web page
}
//========================================================
void SendXML(){

  strcpy(buf,"");
  // Serial.println("sending xml");
  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");
  // send temperature
  sprintf(buf, "<B0>%d.%d</B0>\n", (int) temperature,abs((int) (temperature * 10)  - ((int) (temperature) * 10)));
  strcat(XML, buf);
  // send humidity
  sprintf(buf, "<B1>%d.%d</B1>\n",(int) humidity,abs((int) (humidity * 10)  - ((int) (humidity) * 10)));
  strcat(XML, buf);
  // send pressure
  sprintf(buf, "<B2>%d.%d</B2>\n", (int) pressure,abs((int) (pressure * 10)  - ((int) (pressure) * 10)));
  strcat(XML, buf);
  // send rtc ds1307 date
  sprintf(buf, "<B3>%s</B3>\n",dayStamp.c_str());
  strcat(XML, buf);
  // send rtc ds1307 time
  sprintf(buf, "<B4>%s</B4>\n",timeStamp.c_str());
  strcat(XML, buf);
  //
  sprintf(buf, "<B5>%d</B5>\n", (int) batteryLevel);
  strcat(XML, buf);
  //
  strcat(XML, "</Data>\n");

  // wanna see what the XML code looks like?
  // actually print it to the serial monitor and use some text editor to get the size
  // then pad and adjust char XML[2048]; above
  //Serial.println(XML);

  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/xml", XML);
}
