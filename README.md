# Smart-Room-Controller
Controlling the IoT room

#OVERVIEW:

##Alchemy is a smart room controller inspired by the colors of the atoms that make life. 

Six  Phillips HUE lights are activated by a BME sensor which perceives the humidity in the  human breath, coupled with a Grove Ultrasonic Ranger sensor that establish duration based on the continuous presence of the activating  body. 

When no live presence is sensed, the lights are set on a calming screensaver mood. When activate, they emit the color spectra of chemical elements that compose human and biological bodies, while Wemo Smart Plugs are also switched on.

In addition to the automatic sensing, the room controller offer a manual activation function. Pressing the button on the Alchemy controller, that is couple with the OLED screen, a random chemical element is selected that offer imaginative insights and forecasts into the future. 

A strip of 30 Neopixel LEDs completes the controller and present the colors of the emission spectra of the oracle elements in conjunction with the button activation, and also appearing on the screen for easy identification.


##HOW TO USE:

The accompanying code has been created for Particle Photon II and it is based on the functions described above.  It was written in Visual Studio Code.
 
The code is quite simple and centered around a couple of switch cases syntax. Further streamlining and improvements  can be achieved. Great attention was given to the creation of the colors arrays both for LEDs and Hue lights based on conversions of the wavelengths of measured atomic emissions for  the elements. 

**The project is composed of the following parts:**
- Breadboard;
- Particle Photon II;
- OLED screen;
- BME sensor;
- Grove Ultrasonic Ranger;
-  NeoPixels LEDs strip;
- RGB Rotary Encoder or another button;
- Philips Hue lights 
- Wemo smart plug. 
