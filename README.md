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
			* After the installation, create a new project with any desired name, select "TTGO T-BEAM" at the board selection, leave the framework as "Arduino" then click the "Finish" button.
			* When the project creation is comlete, open the file "platformio.ini", and add a new line with the following:
				> upload_protocol = esptool
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
			* Send [example]().
			* Receive [example]().
			* Send/Receive [example]().
			* LoRa Chat [example]().
			* Great LoRa [tutorial](https://randomnerdtutorials.com/ttgo-lora32-sx1276-arduino-ide/).
		* GPS:
			> The axp20x library is used to power the GPS on, by default, the boards AXP192chip comes with the GPS disabled. 
			> * The AXP192 chip is the power system manager.
				- You can enable / disable different modules of the board with it

			* Get GPS info [example]().
			* GPS + LoRa [example]().
			* Great TinyGPS++ [tutorial](http://arduiniana.org/libraries/tinygpsplus/).
	* Board schematics and pins:
		![image]()