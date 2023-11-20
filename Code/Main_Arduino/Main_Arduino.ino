#include <Adafruit_ILI9341.h>
#include <SoftwareSerial.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ImageReader.h>
#include <SPI.h>
#include <string.h>
/*LCD #defines*/
#define TFT_DC    9
#define TFT_CS    8
#define TFT_MOSI  11
#define TFT_CLK   13
#define TFT_RST   10
#define TFT_MISO  12
#define RX_COMPLETE 3
#define LIGHTS      5
#define LIGHTS_INPUT 2
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
/**********************/


#define LIMIT_SWITCH_PIN 7
#define BUZZER_PIN 6
#define HORN_PIN 4
  SoftwareSerial mySerial(0,1);
int distanceReading;
int speedReading;
float batteryReading;

int getValue(String data, String label) {
  int valueIndex = data.indexOf(label) + label.length();
  return data.substring(valueIndex).toInt();
}


void setup() {
  mySerial.begin(9600);
  pinMode(LIMIT_SWITCH_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer - pin 6 as an output
  pinMode(HORN_PIN, INPUT);
  pinMode(RX_COMPLETE, INPUT);
  pinMode(LIGHTS,OUTPUT);
  pinMode(LIGHTS_INPUT,INPUT);
  tft.begin();
  tft.setRotation(1); //Set rotation to 90 degrees

}
 
void loop() {
    
    while(digitalRead(RX_COMPLETE) == LOW){}
  if(mySerial.available()){
    String data = Serial.readStringUntil('\n');
    Serial.println(data);
    distanceReading = getValue(data, "Distance:");
    speedReading = getValue(data, "Speed:");
    batteryReading = getValue(data,"Voltage:");

  }
  tft.begin();
  tft.setRotation(1);
  tft.setTextSize(2);
  if (digitalRead(LIMIT_SWITCH_PIN) == HIGH)
  {
    tft.println("Car is Locked");
    
  }
 
  else
  {
    tft.println("Car is unlocked");
  }
  if(digitalRead(LIGHTS_INPUT)==HIGH){
    tft.println("Lights are ON");
  }
  else{
    tft.println("Lights are OFF");
  }
  
if(digitalRead(HORN_PIN) == HIGH){
  tone(BUZZER_PIN, 1000); 
}

else{
    noTone(BUZZER_PIN);     
}
if(digitalRead(LIGHTS_INPUT)==HIGH){
  analogWrite(LIGHTS,64);
}
else{
  analogWrite(LIGHTS,0);
}


  tft.print("Distance: ");
  tft.print(distanceReading);
  tft.print("\n");
  tft.print("Speed: ");
  tft.print(speedReading);
  tft.print("km/h");
  tft.print("\n");
  tft.print("Voltage: ");
  tft.print(batteryReading);
  tft.print("\n");
  delay(5000);


}

void DISPLAY_distance(int distanceReading) {
    /* Frame to be sent:
   5A A5 05 82 1200 Data (2 bytes)
   5A A5: Frame header
   05: Data length
   82: Write VPS
   1200: RAM address (2 bytes)
   Xx xx: Data value (2 bytes)
  */
  /*
  Serial.write(FRAME_HEADER_H);                // Header higher Byte
  Serial.write(FRAME_HEADER_L);                // Header lower Byte
  Serial.write(DATA_LENGTH);                   // Data length in Bytes
  Serial.write(WRITE_COMMAND);                 // command for writing to the display
  Serial.write(0x10);                          // Address higher Byte of the variable we're writing in display memory
  Serial.write((byte)0x00);                    // Address higher Byte of the variable we're writing in display memory
  Serial.write(highByte(distanceReading));     // Data Higher Byte
  Serial.write(lowByte(distanceReading));      // Data Lower Byte
  */
}

void DISPLAY_speed(int speedReading) {
   /* Frame to be sent:
   5A A5 05 82 1100 Data (2 bytes)
   5A A5: Frame header
   05: Data length
   82: Write VPS
   1100: RAM address (2 bytes)
   Xx xx: Data value (2 bytes)
  */
  /*
  Serial.write(FRAME_HEADER_H);               // Header higher Byte    
  Serial.write(FRAME_HEADER_L);               // Header lower Byte
  Serial.write(DATA_LENGTH);                  // Data length in Bytes
  Serial.write(WRITE_COMMAND);                // command for writing to the display
  Serial.write(0x12);                         // Address higher Byte of the variable we're writing in display memory
  Serial.write((byte)0x00);                   // Address higher Byte of the variable we're writing in display memory
  Serial.write(highByte(speedReading));       // Data Higher Byte
  Serial.write(lowByte(speedReading));        // Data Lower Byte
  */
}

void DISPLAY_batteryVoltage(int batteryReading) {
    /* Frame to be sent:
   5A A5 05 82 1300 Data (2 bytes)
   5A A5: Frame header
   05: Data length
   82: Write VPS
   1300: RAM address (2 bytes)
   Xx xx: Data value (2 bytes)
  */
  /*
  Serial.write(FRAME_HEADER_H);                 // Header higher Byte
  Serial.write(FRAME_HEADER_L);                 // Header lower Byte
  Serial.write(DATA_LENGTH);                    // Data length in Bytes
  Serial.write(WRITE_COMMAND);                  // command for writing to the display
  Serial.write(0x13);                           // Address higher Byte of the variable we're writing in display memory
  Serial.write((byte)0x00);                     // Address higher Byte of the variable we're writing in display memory
  Serial.write(highByte(batteryReading));       // Data Higher Byte
  Serial.write(lowByte(batteryReading));        // Data Lower Byte
  */
}
