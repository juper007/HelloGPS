#include <HardwareSerial.h>
#include <TinyGPS++.h>

// The serial connection to the GPS module
HardwareSerial MySerial(1);
TinyGPSPlus gps;
char locBuff[30];
char timeBuff[20];

void setup(){
  Serial.begin(115200);
  MySerial.begin(9600, SERIAL_8N1, 16, 17);
}

void loop(){  
  while (MySerial.available() > 0){    
    gps.encode(MySerial.read());
    if (gps.location.isUpdated()){
      sprintf(timeBuff, "%4d/%02d/%02d %02d:%02d:%02d", gps.date.year(), gps.date.month(), gps.date.day(), gps.time.hour(), gps.time.minute(), gps.time.second());
      Serial.print(timeBuff);
      Serial.print("\t");
      sprintf(locBuff, "(%3.06f, %3.06f)", gps.location.lat(), gps.location.lng()); 
      Serial.print(locBuff);
      Serial.print("\t");
      Serial.print(gps.speed.mph(), 0);
      Serial.println("m/h");
      
    }    
  }
}
