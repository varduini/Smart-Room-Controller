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
#include "Grove-Ultrasonic-Ranger.h"
#include <neopixel.h> 


SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
Ultrasonic ultrasonic(D19);


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
int i;
int currentTime;
int lastSecond; 
int humidityCase;
int RangeInCentimeters;
bool lights;
int BUTTONINPUT;
char randNumber;
const int PIXELCOUNT = 30; 


// hue lights number:
const int BULB1=1;
const int BULB2=2;
const int BULB3=3;
const int BULB4=4;
const int BULB5=5;
const int BULB6=6;

//wemo numbers:
const int WEMO4=4;
const int WEMO0=0;

//Encoder pins:
const int SWITCHPIN=D15;
//const int PINA=D9;
//const int PINB=D8;
const int REDPIN= D18;
const int BLUEPIN= D16;
const int GREENPIN= D17;
Button myButton (SWITCHPIN);

//colors arrays:
int Carbon [][3] = { {2, 0, 36}, {76, 0, 255}, {125, 0, 149}, {31, 255, 0}, {123, 255, 0}, {255, 226, 0}, {255, 186, 0}, {255, 0, 0}, {213, 0, 0}};
int Hydrogen [] [3] = { {40, 0, 255}, {0, 239, 255}, {0, 239, 255}, {255, 0, 0}};
int Oxygen [][3] = { {123, 0, 146}, {130, 0, 170}, {128, 0, 210}, {109, 0, 251}, {0, 15, 255}, {0, 118, 255}, {0, 143, 255}, {0, 146, 255}, {0, 152, 255}, {0, 255, 203}, {55, 255, 2}, {94, 255, 0}, {220, 56, 0}, {255, 0, 0}, {208, 0, 0}, {104, 0, 0} };
int Nitrogen [][3] = {{130, 0, 179}, {130, 0, 197}, {88, 0, 255}, {0, 38, 255}, {0, 123, 255}, {0, 137, 255}, {0, 215, 255}, {0, 255, 187}, {0, 255, 140}, {219, 255, 0}, {241, 255, 0}, {255, 209, 0}, {255, 0, 0}, {240, 0, 0}, {176, 0, 0}, {172, 0, 0}, {167, 0, 0}};

int CarbonHue [] [3] = { {44113, 125, 35}, {46836,  125, 255}, {52645,  125, 148}, {20513,  125, 255}, {16519,  125, 255}, {9621,  125, 255}, {7987,  125, 255}, {0,  125, 255}, {0,  125, 212} };
// finish others!!

//Oracle array:
const char Oracle [][20] = {"Carbon","Oxygen", "Hydrogen", "Nitrogen"};
//"Phosporous", "Sulfur", "Flourine", "Calcium", "Magnesium", "Iron"};


Adafruit_BME280 bme;
#define OLED_RESET D4
Adafruit_SSD1306 display (OLED_RESET);
Adafruit_NeoPixel pixel ( PIXELCOUNT , SPI1 , WS2812B );

//neopixel function:
void pixelFillStanby ();
void pixelFillOracle ();
void pixelFillProximity ();

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

//encoder setup
pinMode (SWITCHPIN,INPUT_PULLDOWN);
pinMode (GREENPIN,OUTPUT);
pinMode (BLUEPIN,OUTPUT);

//neopixel setup:
pixel.begin ();
pixel.show (); 
pixel.setBrightness (24);

}

void loop() {

display.clearDisplay();

  //BME reading
  humidRH=bme.readHumidity ();
    Serial.printf ("%i \n", humidRH);

if (humidRH>50) {
humidityCase=1; 
}

else {
  humidityCase=0;
}

switch (humidityCase) {

  case 1: 
    RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
	  Serial.printf("The distance to obstacles in front is: %i\n",RangeInCentimeters);	
	  delay(250);


    while (RangeInCentimeters<10) {
      Serial.printf ("someone is close");
      setHue (BULB1, true, CarbonHue [c%8] [0], CarbonHue [c%8] [1], CarbonHue [c%8] [2]);
      wemoWrite (WEMO0,HIGH);
      wemoWrite (WEMO4,HIGH);
      RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
	    Serial.printf("The distance to obstacles in front is: %i\n",RangeInCentimeters);	
	    delay(250);

      c++;
    }

  case 0:
  setHue (BULB1, true, HueIndigo,i%255, 125); 
  i=i+15;
  wemoWrite (WEMO0,LOW);
  wemoWrite (WEMO4,LOW);

}

// currentTime = millis ();

BUTTONINPUT=digitalRead(SWITCHPIN);

if ( BUTTONINPUT == 1 ) {
  Serial.printf (" Button is pressed \n");
  digitalWrite (GREENPIN,LOW);
  digitalWrite (BLUEPIN,HIGH);
  randNumber = random (0, 3) ; 
   //add more!!
  Serial.printf ("The number is = %i \n",randNumber );
  //setHue (BULB1, true, HueViolet,255, 255);
  switch (randNumber) {

    case 0: {
      for (i=0; i<9; i++) {
        red= Carbon[i] [0];
        green= Carbon [i] [1];
        blue= Carbon [i] [2];
        pixel.setPixelColor (i, red, green, blue);
        pixel.show ();
       }

    }
    case 1: {
     for (i=0; i<9; i++) {
        red= Oxygen [i] [0];
        green= Oxygen [i] [1];
        blue= Oxygen [i] [2];
        pixel.setPixelColor (i, red, green, blue);
        pixel.show ();
       }
    }

    case 2: {
        for (i=0; i<9; i++) {
        red= Hydrogen [i] [0];
        green= Hydrogen [i] [1];
        blue= Hydrogen [i] [2];
        pixel.setPixelColor (i, red, green, blue);
        pixel.show ();
       }
    }

    case 3: {
      for (i=0; i<9; i++) {
        red= Nitrogen [i] [0];
        green= Nitrogen [i] [1];
        blue= Nitrogen [i] [2];
        pixel.setPixelColor (i, red, green, blue);
        pixel.show ();
       }
    }

  }

  //to get colors for neopixels
// for (i=0; i<30; i++) {
// red= Oracle[randNumber][i], [0];
// green= Oracle[randNumber][i], [1];
// blue= Oracle[randNumber] [i], [2];
// pixel.setPixelColor (i, red, green, blue);
// }

// NEED OTHER ARRAYS!!
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor (0,5);
  display.printf ("The oracle is %s \n",Oracle[randNumber] );
  display.display();
  delay (2000);

}

else {
  Serial.printf (" Button is not pressed \n");
  digitalWrite (BLUEPIN,LOW);
  digitalWrite (GREENPIN,HIGH);
  //digitalWrite (REDPIN,HIGH);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor (0,5);
  display.printf ("Press \n for \n Oracle");
  display.display();
}
}


// if (myButton.isClicked ()) {
//   lights=!lights;
// }

// if (lights){
//   //if (( currentTime - lastSecond ) >1000) {
//     //  lastSecond = millis ();
//       digitalWrite (GREENPIN,LOW);
//       digitalWrite (BLUEPIN,HIGH);
//       Serial.printf ("button is pressed \n");
// }

// else {
//   digitalWrite (BLUEPIN,LOW);
//   digitalWrite (GREENPIN,HIGH);
//   Serial.printf ("button is not pressed \n");
// }

  // if (( currentTime - lastSecond ) >2000) {
  //     lastSecond = millis ();
  //     digitalWrite (GREENPIN,HIGH);
  //     digitalWrite (REDPIN,LOW);
  //     digitalWrite (BLUEPIN,HIGH);
  //       Serial.printf ("button is pressed red \n");
  // }

  // if (( currentTime - lastSecond ) >3000) {
  //     lastSecond = millis ();
  //     digitalWrite (GREENPIN,HIGH);
  //     digitalWrite (REDPIN,HIGH);
  //     digitalWrite (BLUEPIN,LOW);
  //        Serial.printf ("button is pressed blue \n");
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
