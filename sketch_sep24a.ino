#include <ESP32_Servo.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display ancho en pixels
#define SCREEN_HEIGHT 32 // OLED display alto en pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


const int potPin = 34;
int potValue = 0;
int val = 0;

const int potPin1 = 35;
int potValue1 = 0;
int val1 = 0;

const int potPin2 = 32;
int potValue2 = 0;
int val2 = 0;

Servo myservo;

void setup() {
  
   Serial.begin(115200);
   Serial.print("Inicializando");
   Serial.println("...");
   
   myservo.attach(26);

  pinMode(34, INPUT);
  pinMode(35, INPUT);
  pinMode(32, INPUT);


   
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

   display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  
   delay(1000);


}

void loop() {


  potValue = 10000 + analogRead(potPin);
  potValue1 = 10000 + analogRead(potPin1);
  potValue2 = 10000 + analogRead(potPin2);
 

 Serial.print(potValue); Serial.print("\t");
 Serial.print(potValue1); Serial.print("\t");
 Serial.print(potValue2); Serial.print("\t");
 delay(250);

  sensorEMG();

}


void sensorEMG(void) {
  
  display.clearDisplay();
  
  
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  
  display.print(F("S1:"));
  display.println(potValue);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.print(F("S2:"));
  display.println(potValue1);
  display.setTextColor(SSD1306_WHITE,SSD1306_BLACK); // Draw 'inverse' text
  display.print(F("S3:"));
  display.println(potValue2);
  



  
  val = analogRead(potPin);
  val = map(val, 0, 4095, 0, 360);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);

  display.display();
 
}
