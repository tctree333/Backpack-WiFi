# Backpack-WiFi
Source code for the game version of the backpack alarm

[Maker Faire Bay Area](https://makerfaire.com/maker/entry/70336/)

# Files
*"backpack_wifi"* is a simplified version with basic css. Within the folder, *"backpack_wifi.ino"* is what you flash to your ESP8266. *"index.h"* is the HTML code for the web interface.

The *"backpack_wifi_fancy"* folder is functionally the same as the normal *"backpack_wifi"* but with fancy CSS animations done by my friend Jad.

# To use
Clone the repository to your computer. Open the folder of your choice with the Arduino IDE. Upload to your ESP8266.

Wire your ESP8266 as shown:
![alt text](https://github.com/tctree333/Backpack-WiFi/blob/master/BackpackAlarm.png "Wiring Diagram")
Blue Wire: SCL (LSM303) -> D1 (D1 Mini)
Green Wire: SDA (LSM303) -> D2 (D1 Mini)
Buzzer + -> D0 (D1 Mini)
Black Wires -> GND (D1 Mini)

# Parts
+ **LSM303DLHC Compass/Accelerometer** - You can get a higher quality one from Adafruit (ID: 1120) for $15 each, or get Chinese knockoffs for ~$2-4.
+ **Wemos D1 Mini** - Any ESP8266 microcontroller will probably work, such as the NodeMCU, but I haven’t tested this. These are around $3-4.
+ **Loud Buzzer** - I’m using a large piezo alarm from Sparkfun (COM-13940). It claims it can reach 78dB(A) at 3 KHz at 3 volts. ~$3
+ **Battery Pack/Voltage Regulator** - You can use pretty much any battery pack as long as it provides sufficient current for the D1 Mini (~100-200 mA). I have a 3.7V, 2500 mAh Li-Po battery connected to a 3.3V voltage regulator, as that was what I had. However, if you’re using more voltage, you may need a heat sink for your voltage regulator. ~$1-2
