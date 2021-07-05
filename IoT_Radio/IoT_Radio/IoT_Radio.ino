/*
 Name:		IoT_Radio.ino
 Created:	6/25/2021 11:26:11 AM
 Author:	render
*/

#include <SoftwareSerial.h>
#include <Wire.h>

#define analog_CONTROL_PIN 2 // Analog pin A3
#define BUTTON_PIN 7 
#define RX 10
#define TX 11

/*
0 - Get WIFI IP info
1 - List WiFi
2 - Connect to SSID
3 - Disconnect from SSID
4 -

Each command must have a range depending on 1024/(number of command)
*/
#define WIFI_IP 0
#define WIFI_LIST_SSID 1
#define WIFI_CONNECT 2
#define WIFI_DISCONNECT 3

SoftwareSerial wifi(RX, TX);

int status = 0;
int max_value;
int current_value;
bool BUTTON_PRESSED = false;
int current_selected_command = -1;

void setup() {
	
	Serial.begin(9600);
	wifi.begin(115200);
	pinMode(analog_CONTROL_PIN, INPUT);
	pinMode(BUTTON_PIN, INPUT);
	status = 0;
}

void loop() {
  
	String echo;
	String command;
	bool send=false;
	float control_level;

	
	control_level = analogRead(analog_CONTROL_PIN); // Может быть до 1023;

	if ( control_level > 0 && control_level < 246) {
		if (current_selected_command != WIFI_IP) {
			Serial.print("Level ");
			Serial.println(control_level);
			Serial.println("Get WIFI IP info");
			current_selected_command = WIFI_IP;
		}
		if ((digitalRead(BUTTON_PIN) == HIGH) && !BUTTON_PRESSED) {
			SendCommand("0");
			BUTTON_PRESSED = true;
		}
	}
	else if (control_level > 267 && control_level < 502) {
		if (current_selected_command != WIFI_LIST_SSID) {
			Serial.print("Level ");
			Serial.println(control_level);
			Serial.println("List WIFI Stations");
			current_selected_command = WIFI_LIST_SSID;
		}
		if ((digitalRead(BUTTON_PIN) == HIGH) && !BUTTON_PRESSED) {
			SendCommand("1");
			BUTTON_PRESSED = true;
		}
	}
	else if (control_level > 523 && control_level < 758) {
		if (current_selected_command != WIFI_CONNECT) {
			Serial.print("Level ");
			Serial.println(control_level);
			Serial.println("Connect to SSID");
			current_selected_command = WIFI_CONNECT;
		}
		if ((digitalRead(BUTTON_PIN) == HIGH) && !BUTTON_PRESSED) {
			SendCommand("2");
			BUTTON_PRESSED = true;
		}
	}
	else if (control_level > 779 && control_level < 1023) {
		if (current_selected_command != WIFI_DISCONNECT) {
			Serial.print("Level ");
			Serial.println(control_level);
			Serial.println("Disconnect from SSID");
			current_selected_command = WIFI_DISCONNECT;
		}
		if ((digitalRead(BUTTON_PIN) == HIGH) && !BUTTON_PRESSED) {
			SendCommand("3");
			BUTTON_PRESSED = true;
		}
	}

	if (digitalRead(BUTTON_PIN) == LOW) {
		BUTTON_PRESSED = false;
	}

	while (wifi.available()) {
		echo = wifi.readString();
		Serial.println(echo);
	}

}

void SendCommand(char *command) {

	Serial.println(command);
	wifi.print(command);
}
