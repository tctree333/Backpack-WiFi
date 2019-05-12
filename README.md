# Backpack-WiFi
Source code for the game version of the backpack alarm

[Maker Faire Bay Area](https://makerfaire.com/maker/entry/70336/)

# Files
`backpack_wifi` is a simplified version with basic css. Within the folder, `backpack_wifi.ino` is what you flash to your ESP8266. `index.h` is the HTML code for the web interface.

The `backpack_wifi_fancy` folder is functionally the same as the normal `backpack_wifi` but with fancy CSS animations done by my friend Jad.

# Flashing Your Device
Clone the repository to your computer. Open the folder of your choice with the Arduino IDE. Upload to your ESP8266.

Wire your ESP8266 as shown:
![alt text](https://github.com/tctree333/Backpack-WiFi/blob/master/BackpackAlarm.png "Wiring Diagram")
+ Blue Wire: SCL (LSM303) -> D1 (D1 Mini)
+ Green Wire: SDA (LSM303) -> D2 (D1 Mini)
+ Buzzer Positive -> D0 (D1 Mini)
+ Black Wires -> GND (D1 Mini)

# To Use
1. After supplying power to the D1 Mini through a battery or USB, use a WiFi enabled device with a web browser such as a computer or tablet. 
2. Navigate to the WiFi settings and connect to the SSID `Backpack_Wifi` with password `12345678`. These values can be changed in the code, around line 15 depending on which file you're using.
3. After connecting to the D1 Mini, use your web browser and go to `192.168.4.1`. If you are using the fancy version, some CSS effects may not be avaliable. To switch to the plain version, go to `192.168.4.1/plain`.
4. To start the game, click **Start**, or press `g` on your keyboard. The timer will start and the D1 Mini should beep.
5. The game will stop automatically if rotation is detected. If the player has completed the course, click **Stop**, or press `s` on your keyboard.
6. To clear the time, click **Clear**, or press `c`.

# Parts
+ **LSM303DLHC Compass/Accelerometer** - You can get a higher quality one from Adafruit (ID: 1120) for $15 each, or get Chinese knockoffs for ~$2-4.
+ **Wemos D1 Mini** - Any ESP8266 microcontroller will probably work, such as the NodeMCU, but I haven’t tested this. These are around $3-4.
+ **Loud Buzzer** - I’m using a large piezo alarm from Sparkfun (COM-13940). It claims it can reach 78dB(A) at 3 KHz at 3 volts. ~$3
+ **Battery Pack/Voltage Regulator** - You can use pretty much any battery pack as long as it provides sufficient current for the D1 Mini (~100-200 mA). I have a 3.7V, 2500 mAh Li-Po battery connected to a 3.3V voltage regulator, as that was what I had. However, if you’re using more voltage, you may need a heat sink for your voltage regulator. ~$1-2
