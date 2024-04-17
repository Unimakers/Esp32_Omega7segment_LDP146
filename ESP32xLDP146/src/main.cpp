#include <Arduino.h>
#include <Hardwa2reSerial.h>
#include <WiFi.h>
#include "time.h"

const char* ssid     = "routeur qui se balade";
const char* password = "Bananas1";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;


HardwareSerial SerialPort(2);

const long interval = 1000*60;
char text[9] = {'U','N','I','M','A','K','E','R','S'};

unsigned long previousMillis = 0;


void Scroll(char txt[]){
  int i;
    for(i=0; i=9;i++){
      SerialPort.print(txt[i]);
      delay(500);
    }
}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay,10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
}

int comp(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return -1;
  }
  struct tm date= {
    0,   // tm_sec (seconds)
    0,   // tm_min (minutes)
    0,   // tm_hour (hours)
    8,  // tm_mday (day of the month)
    5,   // tm_mon (month, 0-based)
    124, // tm_year (year since 1900)
    0,   // tm_wday (day of the week, not used in this example)
    0,   // tm_yday (day of the year, not used in this example)
    0    // tm_isdst (DST - Daylight Saving Time flag, not used in this example)
  };

  time_t time1 = mktime(&timeinfo);
  time_t time2 = mktime(&date);

    double difference = difftime(time2, time1);

    int days = difference / (60 * 60 * 24) - 30;
    Serial.println(days);
    return days;


}


void setup () {
  Serial.begin(9600);

  SerialPort.begin(9600, SERIAL_8N1,-1,17);
  delay(1000);
  SerialPort.write(0x0C);//empty out
  pinMode(35,INPUT);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  //SerialPort.print("WIFI@");
  delay(5000);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  SerialPort.print("WIFI");
  delay(2000);
  SerialPort.write(0x0C);//empty out


  while (digitalRead(35))
  {
    /* code */
  }


  Serial.println("Started");

  SerialPort.print("CDR  ");
  delay(2000);
  SerialPort.write(0x0C);//empty out
  delay(2000);
  SerialPort.print("2024 ");
  delay(2000);
  SerialPort.write(0x0C);//empty out
  delay(2000);
  SerialPort.printf("J - %i",comp());

}

void loop () {

  // for(int i=100; i>0;i--){
  //   SerialPort.write(0X0C);
  //   SerialPort.printf("%i",i);
  //   delay(1000);
  // }
}
