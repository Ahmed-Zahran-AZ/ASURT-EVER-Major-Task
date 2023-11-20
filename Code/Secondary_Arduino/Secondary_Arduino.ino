#include <SoftwareSerial.h>
#define POT_PIN A0
#define VOL_PIN A1
#define ULSONIC_TRIG 9
#define ULSONIC_ECHO 10
#define TX_COMPLETE_FLAG 2
int RPM;
int speed_Kmph;

/*Ultrasonic*/
long duration;
int distance;

/*voltage sensor*/
// Floats for ADC voltage & Input voltage
float adc_voltage = 0.0;
float in_voltage = 0.0;

// Floats for resistor values in divider (in ohms)
float R1 = 30000.0;
float R2 = 7500.0;

// Float for Reference Voltage
float ref_voltage = 5.0;

// Integer for ADC value
int adc_value = 0;
  //Setup the serial communication between the two MCUs
  SoftwareSerial mySerial(0,1);
void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  pinMode(ULSONIC_TRIG, OUTPUT); // Sets the trigPin as an Output
  pinMode(ULSONIC_ECHO, INPUT); // Sets the echoPin as an Input
  pinMode(TX_COMPLETE_FLAG,OUTPUT);
}

void loop() {
  /*TX_COMPLETE_FLAG Clear*/
  digitalWrite(TX_COMPLETE_FLAG,LOW);

  /********************************************************/
  /*Speed in kilometers per hour calculations*/
  /********************************************************/
  RPM = analogRead(POT_PIN);      //Read and save analog value from potentiometer
  speed_Kmph = ((2 * 3.14 * RPM) / 60) * (17 / 2) * (3.6);

  /********************************************************/
  /*UltraSonic*/
  /********************************************************/
  // Clears the trigPin
  digitalWrite(ULSONIC_TRIG, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(ULSONIC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULSONIC_TRIG, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ULSONIC_ECHO, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;

  /********************************************************/
  /*Voltage Sensor*/
  /********************************************************/
  // Read the Analog Input
  adc_value = analogRead(VOL_PIN);

  // Determine voltage at ADC input
  adc_voltage  = (adc_value * ref_voltage) / 1024.0;

  // Calculate voltage at divider input
  in_voltage = adc_voltage * (R1 + R2) / R2;

  /********************************************************/
  /*Send data to main arduino*/
  /********************************************************/
  
  mySerial.print(in_voltage);
  /*mySerial.print(',');
  mySerial.print(distance);
  mySerial.print(',');
  mySerial.print(speed_Kmph);
  mySerial.print('\n');*/
  digitalWrite(TX_COMPLETE_FLAG,HIGH);
  delay(1000);
}
