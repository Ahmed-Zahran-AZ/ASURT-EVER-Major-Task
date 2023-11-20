#define frameHeader_H    0x5A
#define frameHeader_L    0xA5
#define writeCommand     0x82
#define dataLength       0x05

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  DISPLAY_RPM();
  DISPLAY_speed();
  DISPLAY_distance();
  DISPLAY_batteryVoltage();
}

void DISPLAY_distance() {
    /* Frame to be sent:
   5A A5 05 82 1200 Data (2 bytes)
   5A A5: Frame header
   05: Data length
   82: Write VPS
   1200: RAM address (2 bytes)
   Xx xx: Data value (2 bytes)
  */
  void Serial.write(frameHeader_H);                // Header higher Byte
  Serial.write(frameHeader_L);                // Header lower Byte
  Serial.write(dataLength);                   // Data length in Bytes
  Serial.write(writeCommand);                 // command for writing to the display
  Serial.write(0x10);                         // Address higher Byte of the variable we're writing in display memory
  Serial.write((byte)0x00);                   // Address higher Byte of the variable we're writing in display memory
  Serial.write(highByte(data));               // Data Higher Byte
  Serial.write(lowByte(data));                // Data Lower Byte
}

void DISPLAY_RPM(int data) {
  /* Frame to be sent:
   5A A5 05 82 1000 Data (2 bytes)
   5A A5: Frame header
   05: Data length
   82: Write VPS
   1000: RAM address (2 bytes)
   Xx xx: Data value (2 bytes)
  */
  Serial.write(frameHeader_H);            // Header higher Byte
  Serial.write(frameHeader_L);            // Header lower Byte
  Serial.write(dataLength);               // Data length in Bytes
  Serial.write(writeCommand);             // command for writing to the display
  Serial.write(0x11);                     // Address higher Byte of the variable we're writing in display memory
  Serial.write((byte)0x00);               // Address higher Byte of the variable we're writing in display memory
  Serial.write(highByte(data));           // Data Higher Byte
  Serial.write(lowByte(data));            // Data Lower Byte
}

void DISPLAY_speed(int data) {
   /* Frame to be sent:
   5A A5 05 82 1100 Data (2 bytes)
   5A A5: Frame header
   05: Data length
   82: Write VPS
   1100: RAM address (2 bytes)
   Xx xx: Data value (2 bytes)
  */
  Serial.write(frameHeader_H);               // Header higher Byte    
  Serial.write(frameHeader_L);               // Header lower Byte
  Serial.write(dataLength);                  // Data length in Bytes
  Serial.write(writeCommand);                // command for writing to the display
  Serial.write(0x12);                        // Address higher Byte of the variable we're writing in display memory
  Serial.write((byte)0x00);                  // Address higher Byte of the variable we're writing in display memory
  Serial.write(highByte(data));              // Data Higher Byte
  Serial.write(lowByte(data));               // Data Lower Byte
}

void DISPLAY_batteryVoltage() {
    /* Frame to be sent:
   5A A5 05 82 1300 Data (2 bytes)
   5A A5: Frame header
   05: Data length
   82: Write VPS
   1300: RAM address (2 bytes)
   Xx xx: Data value (2 bytes)
  */
  Serial.write(frameHeader_H);                 // Header higher Byte
  Serial.write(frameHeader_L);                 // Header lower Byte
  Serial.write(dataLength);                    // Data length in Bytes
  Serial.write(writeCommand);                  // command for writing to the display
  Serial.write(0x13);                          // Address higher Byte of the variable we're writing in display memory
  Serial.write((byte)0x00);                    // Address higher Byte of the variable we're writing in display memory
  Serial.write(highByte(data));                // Data Higher Byte
  Serial.write(lowByte(data));                 // Data Lower Byte
}
