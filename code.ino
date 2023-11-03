#define FRAME_HEADER_H     0x5A
#define FRAME_HEADER_L     0xA5
#define WRITE_COMMAND      0x82
#define DATA_LENGTH        0x05
#define SPEED_PIN          A0
#define DISTANCE_PIN       A1
#define BATTERY_PIN        A2
#define RPM_PIN            A3

int distanceReading;
int speedReading;
int batteryReading;
int RPM_Reading;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SPEED_PIN,INPUT);
  pinMode(DISTANCE_PIN,INPUT);
  pinMode(BATTERY_PIN,INPUT);
  pinMode(RPM_PIN,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  RPM_Reading     = analogRead(RPM_PIN);
  speedReading    = analogRead(SPEED_PIN);
  batteryReading  = analogRead(BATTERY_PIN);
  distanceReading = analogRead(DISTANCE_PIN);

  DISPLAY_RPM(RPM_Reading);
  DISPLAY_speed(speedReading);
  DISPLAY_distance(distanceReading);
  DISPLAY_batteryVoltage(batteryReading);
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
  Serial.write(FRAME_HEADER_H);                // Header higher Byte
  Serial.write(FRAME_HEADER_L);                // Header lower Byte
  Serial.write(DATA_LENGTH);                   // Data length in Bytes
  Serial.write(WRITE_COMMAND);                 // command for writing to the display
  Serial.write(0x10);                          // Address higher Byte of the variable we're writing in display memory
  Serial.write((byte)0x00);                    // Address higher Byte of the variable we're writing in display memory
  Serial.write(highByte(distanceReading));     // Data Higher Byte
  Serial.write(lowByte(distanceReading));      // Data Lower Byte
}

void DISPLAY_RPM(int RPM_Reading) {
  /* Frame to be sent:
   5A A5 05 82 1000 Data (2 bytes)
   5A A5: Frame header
   05: Data length
   82: Write VPS
   1000: RAM address (2 bytes)
   Xx xx: Data value (2 bytes)
  */
  Serial.write(FRAME_HEADER_H);             // Header higher Byte
  Serial.write(FRAME_HEADER_L);             // Header lower Byte
  Serial.write(DATA_LENGTH);                // Data length in Bytes
  Serial.write(WRITE_COMMAND);              // command for writing to the display
  Serial.write(0x11);                       // Address higher Byte of the variable we're writing in display memory
  Serial.write((byte)0x00);                 // Address higher Byte of the variable we're writing in display memory
  Serial.write(highByte(RPM_Reading));      // Data Higher Byte
  Serial.write(lowByte(RPM_Reading));       // Data Lower Byte
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
  Serial.write(FRAME_HEADER_H);               // Header higher Byte    
  Serial.write(FRAME_HEADER_L);               // Header lower Byte
  Serial.write(DATA_LENGTH);                  // Data length in Bytes
  Serial.write(WRITE_COMMAND);                // command for writing to the display
  Serial.write(0x12);                         // Address higher Byte of the variable we're writing in display memory
  Serial.write((byte)0x00);                   // Address higher Byte of the variable we're writing in display memory
  Serial.write(highByte(speedReading));       // Data Higher Byte
  Serial.write(lowByte(speedReading));        // Data Lower Byte
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
  Serial.write(FRAME_HEADER_H);                 // Header higher Byte
  Serial.write(FRAME_HEADER_L);                 // Header lower Byte
  Serial.write(DATA_LENGTH);                    // Data length in Bytes
  Serial.write(WRITE_COMMAND);                  // command for writing to the display
  Serial.write(0x13);                           // Address higher Byte of the variable we're writing in display memory
  Serial.write((byte)0x00);                     // Address higher Byte of the variable we're writing in display memory
  Serial.write(highByte(batteryReading));       // Data Higher Byte
  Serial.write(lowByte(batteryReading));        // Data Lower Byte
}
