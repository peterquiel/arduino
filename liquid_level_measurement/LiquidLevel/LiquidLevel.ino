/* YourDuino.com Example Software Sketch
   20 character 4 line I2C Display
   Backpack Interface labelled "YwRobot Arduino LCM1602 IIC V1"
   Connect Vcc and Ground, SDA to A4, SCL to A5 on Arduino
   terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here:
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

#include <math.h>
/*-----( Declare Constants )-----*/
/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

static const int trigPin = 7;
static const int echoPin = 6;

/*speed of sound adjusted to the temperature in m/s*/
float speed_of_sound(float temperature) {
  float adjustment = 0.606 * temperature;
  float speedOfSound = 315.5 + adjustment;
  return speedOfSound;
}

float distance(long microseconds) {
  float seconds = (float) microseconds / 1000000;
  float speedOfSound = speed_of_sound(10);
  return (seconds * speedOfSound) / 2;
}
// calc the volume of a liquid in a partly filled cylinder. taken from https://de.wikipedia.org/wiki/Zylinder_(Geometrie)#Volumenberechnung_eines_liegenden_Kreiszylinders_.28Tank-Problem.29
float liquid_volume(float length, float radius, float liquid_level) {
 return pow(radius, 2) * lenght * (acos( (radius - liquid_level) / radius) - (radius- liquid_level) * (sqrt(2*radius*liquid_level - pow(liquid_level, 2))/pow(radius,2)));
}

float cylinder_volume(float length, float radius) {
  return M_PI * pow(radius, 2) * lenght;
}

void setup() {
  Serial.begin(9600);  // Used to type in characters
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.begin(16,2);         // initialize the lcd for 20 chars 4 lines, turn on backlight

  // ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on
}/*--(end setup )---*/
float temperature ,meter;
long duration;
char strOut[8];

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  meter = distance(duration);
  dtostrf(meter, 1, 3, strOut);
  lcd.clear();
  lcd.write("Distance:");
  lcd.write(strOut);
  lcd.write("m");
  /*sprintf(strOut, "%5d", temperature);*/
  /*lcd.write(strOut);*/
  delay(1000);
  Serial.print("Distance");
  Serial.print(strOut);
  Serial.print(";");
  Serial.print(temperature);
  Serial.print(";");
  Serial.println(meter);
}
