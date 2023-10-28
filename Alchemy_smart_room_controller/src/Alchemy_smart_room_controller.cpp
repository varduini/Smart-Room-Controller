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
int f;
int mg;
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
int y;
int p, r, g, b, m;

// hue lights number:
const int BULB1=1;
const int BULB2=2;
const int BULB3=3;
const int BULB4=4;
const int BULB5=5;
const int BULB6=6;
const int TOTALBULBS = 6;

//wemo numbers:
const int WEMO4=4;
const int WEMO0=0;

//Encoder pins:
const int SWITCHPIN=D15;
const int BLUEPIN= D16;
const int GREENPIN= D17;
Button myButton (SWITCHPIN);

//colors arrays:
int Carbon [][3] = { {2, 0, 36}, {76, 0, 255}, {125, 0, 149}, {31, 255, 0}, {123, 255, 0}, {255, 226, 0}, {255, 186, 0}, {255, 0, 0}, {213, 0, 0}};
int Hydrogen [] [3] = { {129,0,169}, {40, 0, 255}, {0, 239, 255}, {255, 0, 0}};
int Oxygen [][3] = { {123, 0, 146}, {130, 0, 170}, {128, 0, 210}, {109, 0, 251}, {0, 15, 255}, {0, 118, 255}, {0, 143, 255}, {0, 146, 255}, {0, 152, 255}, {0, 255, 203}, {55, 255, 2}, {94, 255, 0}, {220, 56, 0}, {255, 0, 0}, {208, 0, 0}, {104, 0, 0} };
int Nitrogen [][3] = {{130, 0, 179}, {130, 0, 197}, {88, 0, 255}, {0, 38, 255}, {0, 123, 255}, {0, 137, 255}, {0, 215, 255}, {0, 255, 187}, {0, 255, 140}, {219, 255, 0}, {241, 255, 0}, {255, 209, 0}, {255, 0, 0}, {240, 0, 0}, {176, 0, 0}, {172, 0, 0}, {167, 0, 0}};
int Flourine [] [3] = { {0, 40, 255}, {0, 243, 255}, {0, 255, 203}, {0, 255, 146}, {45, 255, 0}, {255, 173, 0}, {255, 99,0},{255, 52, 0}, {255, 0, 0}};
int Magnesium [] [3]= {{0, 70, 255}, {0, 255, 203}, {45, 255, 0}, {163, 255, 0}, {255, 137, 9}, {255, 0, 0} };

int CarbonHue [] [3] = { {44113, 125, 35}, {46836,  125, 255}, {52645,  125, 148}, {20513,  125, 255}, {16519,  125, 255}, {9621,  125, 255}, {7987,  125, 255}, {0,  125, 255}, {0,  125, 212} };
int HydrogenHue [] [3]= { {51919, 255, 168}, {45202, 255, 255}, {33402, 255, 255}, {0, 255, 255} };
int OxygenHue [] [3]= { {52827, 255, 145}, {51919, 255, 170}, {50285, 255, 209}, {48288, 255, 249}, {42842, 255, 255}, {38485, 255, 255}, {37396, 255, 255}, {37396, 255, 255}, {37033, 255, 255}, {30498, 255, 255}, {19424, 252, 255}, {17790, 255, 255}, {2723, 255, 219}, {0, 255, 255}, {0, 255, 206}, {0, 255, 102}};
int NitrogenHue [] [3]= {{51556, 255, 178}, {50830, 255, 196}, {47380, 255, 255}, {41934, 255, 255}, {38304, 255, 255}, {37759, 255, 255}, {34310, 255, 255}, {29771, 255, 255}, {27775, 255, 255}, {12344, 255, 255}, {11436, 255, 255}, {8895, 255, 255}, {o, 255, 255}, {0, 255, 239}, {0, 255, 176}, {0, 255, 170}, {0, 255, 165} };
int FlourineHue [] [3] = { {41934, 255, 255}, {33221, 255, 255}, {30498, 255, 255}, {27956, 255, 255}, {19787, 255, 255}, {7442, 255, 255}, {4175, 255, 255}, {2178, 255, 255}, {0, 255, 255}};
int MagnesiumHue [] [3] = {{40664, 255, 255}, {30498, 255, 255}, {19787, 255, 255}, {14885, 255, 255}, {5809, 255, 255}, {0, 255, 255}}; 

//Oracle array:
const char Oracle [][20] = {"Carbon","Oxygen", "Hydrogen", "Nitrogen","Flourine", "Magnesium"};


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


    while (RangeInCentimeters<50) {
      Serial.printf ("someone is close");
      setHue (BULB1, true, CarbonHue [c%9] [0], CarbonHue [c%9] [1], CarbonHue [c%9] [2]);
      setHue (BULB2, true, OxygenHue [o%16] [0], OxygenHue [o%16] [1], OxygenHue [o%16] [2]);
      setHue (BULB3, true, HydrogenHue [h%4] [0], HydrogenHue [h%4] [1], HydrogenHue[h%4] [2]);
      setHue (BULB4, true, NitrogenHue [n%17] [0], NitrogenHue [n%17] [1], NitrogenHue [n%17] [2]);
      setHue (BULB5, true, FlourineHue [f%9] [0], FlourineHue [f%9] [1], FlourineHue [f%9] [2]);
      setHue (BULB6, true, MagnesiumHue [mg%6] [0], MagnesiumHue [mg%6] [1], MagnesiumHue [mg%6] [2]);

      wemoWrite (WEMO0,HIGH);
      wemoWrite (WEMO4,HIGH);
      RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
	    Serial.printf("The distance to obstacles in front is: %i\n",RangeInCentimeters);	
	    delay(250);

      c++;
      o++;
      n++;
      h++;
      f++;
      m++;

    }

  case 0:
  
for (int x=0; x<TOTALBULBS; x++) {
  setHue (x, true, HueIndigo,i%255, 125);
//   setHue (BULB2, true, HueIndigo,i%255, 125); 
// setHue (BULB3, true, HueIndigo,i%255, 125); 
//  setHue (BULB4, true, HueIndigo,i%255, 125); 
// setHue (BULB5, true, HueIndigo,i%255, 125); 
//   setHue (BULB6, true, HueIndigo,i%255, 125); 
  i=i+15;
  wemoWrite (WEMO0,LOW);
  wemoWrite (WEMO4,LOW);

  m=p%30;
  r=p%255;
  g=p%255;
  b=p%255;
  p++;
 pixel.setPixelColor (m, 3*r, g, 255);
       
        pixel.show ();
        

        }

// currentTime = millis ();

BUTTONINPUT=digitalRead(SWITCHPIN);

if (BUTTONINPUT == 1 ) {
  Serial.printf (" Button is pressed \n");
  digitalWrite (GREENPIN,LOW);
  digitalWrite (BLUEPIN,HIGH);
  randNumber = random (0, 5) ; 
  pixel.clear();
   //add more!!

  Serial.printf ("The number is = %i \n",randNumber );
  //setHue (BULB1, true, HueViolet,255, 255);

  switch (randNumber) {

    case 0: {
      for (i=0; i<9; i++) {
        red= Carbon[i] [0];
        green= Carbon [i] [1];
        blue= Carbon [i] [2];
        pixel.setPixelColor (3*i, red, green, blue);
        Serial.printf ("pixels on carbon");
        pixel.show ();
       }
    break;

    }
    case 1: {
     for (i=0; i<16; i++) {
        red= Oxygen [i] [0];
        green= Oxygen [i] [1];
        blue= Oxygen [i] [2];
        pixel.setPixelColor (i, red, green, blue);
        Serial.printf ("pixels on oxygen");
        pixel.show ();
       }
    break;
    }

    case 2: {
        for (i=0; i<4; i++) {
          red= Hydrogen [i] [0];
          green= Hydrogen [i] [1];
          blue= Hydrogen [i] [2];
          pixel.setPixelColor (7*i, red, green, blue);
          Serial.printf ("pixels on hydrogen");
          pixel.show ();
       }
       break;
    }

    case 3: {
      for (i=0; i<17; i++) {
        red= Nitrogen [i] [0];
        green= Nitrogen [i] [1];
        blue= Nitrogen [i] [2];
        pixel.setPixelColor (i, red, green, blue);
        Serial.printf ("pixels on nitrogen");
        pixel.show ();
       }
      
      break;
    }
  case 4: {
      for (i=0; i<9; i++) {
        red= Flourine [i] [0];
        green= Flourine [i] [1];
        blue= Flourine [i] [2];
        pixel.setPixelColor (i, red, green, blue);
        Serial.printf ("pixels on flourine");
        pixel.show ();
       }
       break;
    }
    case 5: {
      for (i=0; i<6; i++) {
        red= Magnesium [i] [0];
        green= Magnesium [i] [1];
        blue= Magnesium [i] [2];
        pixel.setPixelColor (i, red, green, blue);
        Serial.printf ("pixels on magnesium");
        pixel.show ();
       }
       break;
    }
  }


  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor (0,5);
  display.printf ("The oracle is %s \n",Oracle[randNumber] );
  display.display();
  delay (2000);
  pixel.clear ();
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

}


  // bool setHue(int lightNum, bool HueOn, int HueColor, int HueBright, int HueSat);
