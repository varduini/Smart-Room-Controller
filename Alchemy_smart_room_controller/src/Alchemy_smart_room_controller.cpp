/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */


#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include <Encoder.h>
#include "Adafruit_BME280.h"
#include "Adafruit_GFX.h" //don't install this one, included in SSD1306
#include "Adafruit_SSD1306.h"

SYSTEM_MODE(MANUAL);

//variables:
int color;
int humidRH;
int brightness;
bool status;
bool changeState;
int c;
int o;
int h;
int n;
int red;
int blue;
int green;
//int HueColor;
int i;
int currentTime;
int lastSecond; 

// hue lights number:
const int BULB1=1;
const int BULB2=2;
const int BULB3=3;
const int BULB4=4;
const int BULB5=5;
const int BULB6=6;

//Encoder pins:
const int BUTTONPIN=D15;
//const int PINA=D9;
//const int PINB=D8;
const int REDPIN= D18;
const int BLUEPIN= D16;
const int GREENPIN= D17;

//Ranger pins:
const int TRIGPIN= D19;
const int ECHOPIN= A2; //analog read

//colors arrays:
int Carbon [][3] = { {2, 0, 36}, {76, 0, 255}, {125, 0, 149}, {31, 255, 0}, {123, 255, 0}, {255, 226, 0}, {255, 186, 0}, {255, 0, 0}, {213, 0, 0}};
int Hydrogen [] [3] = { {40, 0, 255}, {0, 239, 255}, {0, 239, 255}, {255, 0, 0}};
int Oxygen [][3] = { {123, 0, 146}, {130, 0, 170}, {128, 0, 210}, {109, 0, 251}, {0, 15, 255}, {0, 118, 255}, {0, 143, 255}, {0, 146, 255}, {0, 152, 255}, {0, 255, 203}, {55, 255, 2}, {94, 255, 0}, {220, 56, 0}, {255, 0, 0}, {208, 0, 0}, {104, 0, 0} };
int Nitrogen [][3] = {{130, 0, 179}, {130, 0, 197}, {88, 0, 255}, {0, 38, 255}, {0, 123, 255}, {0, 137, 255}, {0, 215, 255}, {0, 255, 187}, {0, 255, 140}, {219, 255, 0}, {241, 255, 0}, {255, 209, 0}, {255, 0, 0}, {240, 0, 0}, {176, 0, 0}, {172, 0, 0}, {167, 0, 0}};

int CarbonHue [] [3] = { {44113, 125, 35}, {46836,  125, 255}, {52645,  125, 148}, {20513,  125, 255}, {16519,  125, 255}, {9621,  125, 255}, {7987,  125, 255}, {0,  125, 255}, {0,  125, 212} };
// finish others!!

//functions:
// bool saveTheMonitor (int HueColor, int HueBright, int HueSat);

Button myButton (BUTTONPIN);
Adafruit_BME280 bme;
#define OLED_RESET D4
Adafruit_SSD1306 display (OLED_RESET);
//Encoder myEnc (PINA, PINB);

//SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);



void setup() {

Serial.begin(9600);

status=bme.begin (0x76);
    delay(2000);
    if (status==false) {
        Serial.printf ("BME280 at address 0x76 X failed to start" );
}
else {
Serial.printf ("All good\n" );  
}
 delay (5000);

  //wifi set up for Hue lights and Wemos:
  WiFi.on ();
  WiFi.clearCredentials ();
  WiFi.setCredentials ("IoTNetwork");
  WiFi.connect ();

//OLED setuo
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 

//BME setup
 status=bme.begin (0x76);
    delay(2000);
}

void loop() {

//clear OLED screen:
  //display.clearDisplay();

// how to set screensaver mood?!?!

// for (i=0; i<=255; i++) {
//   for (i=255; i>0; i--) {
//     if (( currentTime-lastSecond) >1000) {
//       lastSecond = millis ();
// setHue (BULB5, true, HueIndigo, 125,i);
// }
// }
// } 
//color++; 

//setHue (BULB5, false, 0, 0,0); //turn it off


  //if BME hum triggered
  humidRH=bme.readHumidity ();
    Serial.printf ("%i \n", humidRH);

if (humidRH>65) {
  // while ranger detects
  Serial.printf ("trigger");

changeState=!changeState;

if (changeState) {
   for (c=0; c<=8; c++) {
      //for (c=8; c>0; c--);
  setHue (BULB5, true, CarbonHue [c] [0], CarbonHue [c] [1], CarbonHue [c] [2]); 
   // changeState=! changeState;
}  
} 
}

else {
  for (i=0; i<=255; i++) {
//   for (i=255; i>0; i--) {
setHue (BULB5, true, HueIndigo, 125,i);
}
}

//to get colors for neopixels
//  for (i=0; i<9; i++) {
//   red= Carbon [i], [0];
//   green= Carbon [i], [1];
//   blue= Carbon [i], [2];
//   pixel.SetPixelColor (i, red, green, blue);
// }
// NEED OTHER ARRAYS!!

// 

  //if (changeState) {
   

//}
}

// bool saveTheMonitor (int HueColor, int HueBright, int HueSat) {
// static int PrevLightNum;
// static int PrevOn;
// static int PrevColor;
// static int PrevBright;
// static int PrevSat;
// static int HueColor;
// static int HueBright;
// static int HueSat;

// if((HueColor==PrevColor)&&(HueBright==PrevBright)&&(HueSat==PrevSat)) {
//     return false;
//   }
// else {
//   return true;
// }
//   PrevLightNum=lightNum;
//   PrevOn=HueOn;
//   PrevColor=HueColor;
//   PrevBright=HueBright;
//   PrevSat=HueSat;

// }

  //   setHue (BULB2, true, Hydrogen, 255,255); 
  //   for (h=0; h<=3; h++);
  //     for (h=3; h>0; h--);
  //   setHue (BULB3, true, Oxygen, 255,255); 
  //   for (o=0; o<=15; o++);
  //     for (o=15; o>0; o--);
  //       setHue (BULB3, true, Nitrogen, 255,255); 
  //   for (n=0; n<=16; n++);
  //     for (n=16; n>0; n--);

  // bool setHue(int lightNum, bool HueOn, int HueColor, int HueBright, int HueSat);




//else {
//setHue (BULB, false, 0, 0,0); //turn it off
 
  // 
  
//}
