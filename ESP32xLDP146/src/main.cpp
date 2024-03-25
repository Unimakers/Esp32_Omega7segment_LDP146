#include <Arduino.h>
#include <HardwareSerial.h>


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

void setup () {
  Serial.begin(9600);

  SerialPort.begin(9600, SERIAL_8N1,-1,17);
  delay(1000);
  SerialPort.write(0x0C);//empty out

  Serial.println("Started");
}

void loop () {

  for(int i=100; i>0;i--){
    SerialPort.write(0X0C);
    SerialPort.printf("%i",i);
    delay(1000);
  }
}
