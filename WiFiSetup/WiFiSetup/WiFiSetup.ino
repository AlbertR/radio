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

// Number of wifi networks
int scanNetworkResult = 0;
String ssid;
uint8_t encryptionType;
int32_t RSSI;
uint8_t* BSSID;
int32_t channel;
bool isHidden;

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
		case '0': // WIFI status
			switch (WiFi.status()) {
			case WL_IDLE_STATUS:
				Serial.print("IDLE");
				break;
			case WL_NO_SSID_AVAIL:
				Serial.print("NO SSID AVAILABLE");
				break;
			case WL_CONNECTED:
				Serial.println("CONNECTED");
				Serial.print(WiFi.localIP());
				break;
			case WL_CONNECT_FAILED:
				Serial.print("CONNECT FAILED");
				break;
			case WL_WRONG_PASSWORD:
				Serial.print("CONNECT WRONG PASSWORD");
				break;
			case WL_DISCONNECTED:
				Serial.print("DISCONNECTED");
				break;
			default:
				Serial.print("Unknown");
				break;
			}
		case '1': // List WiFi stations
			GetWiFiList();
			break;
		case '2': // Connect to SSID
			break;
		case '3': // Dissconnect from SSID
			break;
		default:
			break;
		}
	}

}

void GetWiFiList() {
	if (WiFi.status() == WL_CONNECTED) {
		scanNetworkResult = WiFi.scanNetworks(false, true);
		if (scanNetworkResult == 0) {
			Serial.print("No wifi networks found");
		}
		else if (scanNetworkResult > 0) {
			for (int8_t i = 0; i < scanNetworkResult; i++) {
				WiFi.getNetworkInfo(i, ssid, encryptionType, RSSI, BSSID, channel, isHidden);
				Serial.printf("%s\n", ssid.c_str());
			}
			delay(0);
		}
		else {
			Serial.print("Scan network failed");
		}
	}
}

void GetRadioStationList() {
	// Update station list
	// Get from site
}

void ConnectToSSID(String SSID, String Password) {
	WiFi.begin(SSID, Password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
	}
}

void DisconnectFromSSID() {
	WiFi.disconnect();
}