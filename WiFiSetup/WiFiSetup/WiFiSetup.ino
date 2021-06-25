/*
 Name:		WiFiSetup.ino
 Created:	6/25/2021 11:26:51 AM
 Author:	render
*/

#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <Wire.h>

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(115200);
	WiFi.mode(WIFI_STA);

	WiFi.disconnect();
	delay(100);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
	char command[] = "";
	int i = 0;
	while (Serial.available()) {
		command[i] = Serial.read();
		i++;

		//Serial.write("Done");
	}
	
	delay(100);

	switch (command[0]) {
	case 48: // Command 0
		Serial.write("100");
		Serial.write("Done");
		break;
	case 49: // Command 1
		Serial.write("200");
		Serial.write("Done");
		break;
	default:
		break;
	}


}

void GetWiFiList() {

}

void GetRadioStationList() {

}

void ConnectToSSID() {

}

void DisconnectFromSSID() {

}