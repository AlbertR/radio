/*
 Name:		WiFiSetup.ino
 Created:	6/25/2021 11:26:51 AM
 Author:	Igor Ushakov
*/

#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#ifndef SSID
#define WIFISSID "g9e"
#define WIFISSIDPW "2kgTUT~9Dw"
#endif

const char * SSID = WIFISSID;
const char * PW = WIFISSIDPW;

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(115200);

	WiFi.mode(WIFI_STA);
	WiFi.begin(SSID, PW);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
	}
}

// the loop function runs over and over again until power down or reset
void loop() {

	if (Serial.available() > 0) {
		switch (Serial.read())
		{
		case '0':
			switch (WiFi.status()) {
			case '0':
				Serial.print("IDLE");
				break;
			case '1':
				Serial.print("NO SSID AVAILABLE");
				break;
			case WL_CONNECTED:
				Serial.println("CONNECTED");
				Serial.print(WiFi.localIP());
				break;
			case '4':
				Serial.print("CONNECT FAILED");
				break;
			case '6':
				Serial.print("CONNECT WRONG PASSWORD");
				break;
			case '7':
				Serial.print("DISCONNECTED");
				break;
			default:
				Serial.print("Unknown");
				break;
			}
			break;
		default:
			break;
		}
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