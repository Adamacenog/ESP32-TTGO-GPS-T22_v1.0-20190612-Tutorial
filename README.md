# Tutorial on how to upload sketches to the ESP32 TTGO GPS-T22_v1.0-20190612 Board, and basic usage of the built in GPS and LoRa.

* ## Before you start:
	* CONECT THE LORA ANTENNA TO THE BOARD, DO NOT POWER ON THE BOARD WITHOUT THE LORA ANTENNA OR YOU MIGHT DAMAGE IT!
	* Install the following driver on your computer:
		* Silicon Labs - CP210x: Download [here](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) 
			> this driver is used by your computer to open a serial comunitation with your board.
	* Environment setup:
		* Arduino IDE:
			* Add the following url in "Additional Board Manager URLs" at File -> Preferences:
				> https://dl.espressif.com/dl/package_esp32_index.json
			
				then click Ok, go to Tools -> Board -> Boards Manager, search and install "ESP32 by Espressif Systems", or follow this [guide](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/).
			* After you install the board software, just select on the boards menu "TTGO T1", set the upload speed to 115200, leave the rest as is and you are going to be able to upload sketches to your TTGO board.
		* VSCode:
			* Install the [PlatformIO](https://platformio.org/?utm_source=platformio&utm_medium=piohome) extention.
			> BEAWARE: PlatformIO is not reliable and its use is not advised!
			> 
			> We are only adding its mention to this tutorial because it is a well known extension used by many people.

			* After the installation, create a new project with any desired name, select "TTGO T-BEAM" at the board selection, leave the framework as "Arduino" then click the "Finish" button.
			* When the project creation is comlete, open the file "platformio.ini", and add a new line with the following:
				> upload_protocol = esptool
				> 
				> upload_speed = 115200

	* Needed libraries:
		* Lora:
			* LoRa by Sandeep Mistry - [link](https://github.com/sandeepmistry/arduino-LoRa).
			* Arduino default [SPI library](https://www.arduino.cc/en/reference/SPI).
			* Arduino default [Wire library](https://www.arduino.cc/en/reference/wire).
		* GPS:
			* TinyGPS++ by Mikal Hart - [link](https://github.com/mikalhart/TinyGPSPlus/releases).
			* axp20x by Lewis He - [link](https://github.com/lewisxhe/AXP202X_Library).
	* Examples:
		#### Disclaimer: some of those examples were taken from [LilyGO](https://github.com/LilyGO/TTGO-T-Beam) github account.
		* LoRa:
			* Send [example](https://github.com/Adamacenog/ESP32-TTGO-GPS-T22_v1.0-20190612-Tutorial/tree/master/LoRa/ESP32-LoRa-sender).
			* Receive [example](https://github.com/Adamacenog/ESP32-TTGO-GPS-T22_v1.0-20190612-Tutorial/tree/master/LoRa/ESP32-LoRa-receiver).
			* Send/Receive [example](https://github.com/Adamacenog/ESP32-TTGO-GPS-T22_v1.0-20190612-Tutorial/tree/master/LoRa/ESP32-LoRa-sender-receiver).
			* LoRa Chat [example](https://github.com/Adamacenog/ESP32-TTGO-GPS-T22_v1.0-20190612-Tutorial/tree/master/LoRa/LoRa-Chat).
			* Great LoRa [tutorial](https://randomnerdtutorials.com/ttgo-lora32-sx1276-arduino-ide/).
		* GPS:
			> The axp20x library is used to power the GPS on, by default, the boards AXP192chip comes with the GPS disabled. 
			> * The AXP192 chip is the power system manager.
				- You can enable / disable different modules of the board with it
			> The GPS chip takes a while to synchronize the first time (~ 5min), and it needs at least 5 sattelites to show the coordinates!

			* Get GPS info [example](https://github.com/Adamacenog/ESP32-TTGO-GPS-T22_v1.0-20190612-Tutorial/tree/master/GPS/ESP32-GPS).
			* GPS + LoRa [example](https://github.com/Adamacenog/ESP32-TTGO-GPS-T22_v1.0-20190612-Tutorial/tree/master/GPS/LoRa%20%2B%20GPS).
			* Great TinyGPS++ [tutorial](http://arduiniana.org/libraries/tinygpsplus/).
	* Board schematics and pins:
		![image](https://github.com/Adamacenog/ESP32-TTGO-GPS-T22_v1.0-20190612-Tutorial/blob/master/Images/ESP32%20schematics.jpeg)