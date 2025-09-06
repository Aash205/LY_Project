//#include <SPI.h>
//#include <LoRa.h>

#include <Wire.h>
//#include <DFRobot_QMC5883.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

//DFRobot_QMC5883 compass;

int RXPin = 10;
int TXPin = 11;

int GPSBaud = 9600;


SoftwareSerial gpsSerial(10, 11);
TinyGPSPlus gps;
int Number_of_SATS;

// Set your destination latitude and longitude here
double destLat = 0.0; //19.073532; // 19.073188 (402); // 19.248979 (kyn); 19.248979;
double destLng = 0.0; //72.899375; // 72.900238 (402);  //73.152404 (kyn); 73.152404;

int direction = 0;
double distance, bearing;
float headingDegrees = 0.0;

#define m11 3
#define m12 9
#define m21 5
#define m22 6

#define D0 2 
#define D1 4 
#define D2 17 
#define D3 16 
#define D4 15 

int dtmf_no = 69;

int count_lboth = 0, count_l = 0, count_r = 0;
int sp = 40;
int f = 0, b = 0, r = 0, l = 0, onr = 0, ol = 0;
bool motion = false;


#define MAX_DIST 500
//bool max_dist = false;
#define echoPin_left 7 //2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin_left 12 //attach pin D4 Arduino to pin Trig of HC-SR04

#define echoPin_right 14//19 //14 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin_right 13//5 //20 //attach pin D4 Arduino to pin Trig of HC-SR04
#define BUZZ 21

// defines variables
long duration_left; // variable for the duration of sound wave travel
int distance_left; // variable for the distance measurement

long duration_right; // variable for the duration of sound wave travel
int distance_right; // variable for the distance measurement

bool autonomous = false;

void setup()
{
  Serial.begin(9600);
//gps
  gpsSerial.begin(GPSBaud);

  
  //Dtmf
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);

  //Motor
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);

  //Ultrasonic
  pinMode(trigPin_left, OUTPUT); // Sets the trigPin_left as an OUTPUT
  pinMode(echoPin_left, INPUT); // Sets the echoPin_left as an INPUT
  pinMode(trigPin_right, OUTPUT); // Sets the trigPin_left as an OUTPUT
  pinMode(echoPin_right, INPUT); // Sets the echoPin_left as an INPUT
  pinMode(BUZZ, OUTPUT);
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
    Stop();

  //LoRa
  //  while (!Serial);
  //  Serial.println("LoRa Receiver");
  //  if (!LoRa.begin(450E6)) {
  //    Serial.println("Starting LoRa failed!"); Stop();
  //  }

//  //compass
//  while (!compass.begin())
//  {
//    Serial.println("Could not find a valid QMC5883 sensor, check wiring!");
//    delay(500);
//  }
//  if (compass.isHMC()) {
//    Serial.println("Initialize HMC5883");
//    compass.setRange(HMC5883L_RANGE_1_3GA);
//    compass.setMeasurementMode(HMC5883L_CONTINOUS);
//    compass.setDataRate(HMC5883L_DATARATE_15HZ);
//    compass.setSamples(HMC5883L_SAMPLES_8);
//  }
//  else if (compass.isQMC()) {
//    Serial.println("Initialize QMC5883");
//    compass.setRange(QMC5883_RANGE_2GA);
//    compass.setMeasurementMode(QMC5883_CONTINOUS);
//    compass.setDataRate(QMC5883_DATARATE_50HZ);
//    compass.setSamples(QMC5883_SAMPLES_8);
//  }

  motion = false;
  //  delay(5000);
  //  f=2;
  //  forward(f);
}


void loop()
{

while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();
  
  dtmf();
  ultrasonic_left();
  ultrasonic_right();

  if (distance_right <= MAX_DIST || distance_left <= MAX_DIST)
  {
    // Displays the distance on the Serial Monitor
    Serial.print("Distance left: ");
    Serial.print(distance_left);
    Serial.print(" cm");
    Serial.print("      Distance Right: ");
    Serial.print(distance_right);
    Serial.println(" cm");
    checkObstacles();
  }

}

void displayInfo()
{
  int n = (int )(gps.satellites.value());
  Serial.println(n);
  if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
  }
  else
  {
    Serial.println("Location: Not Available");
  }
  
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.println();
  Serial.println();
  delay(1000);
}
