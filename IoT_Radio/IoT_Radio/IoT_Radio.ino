/*
 Name:		IoT_Radio.ino
 Created:	6/25/2021 11:26:11 AM
 Author:	render
*/

#include <SoftwareSerial.h>
#include <Wire.h>

// the setup function runs once when you press reset or power the board
void setup() {
	
	Serial.begin(115200);

}

// the loop function runs over and over again until power down or reset
void loop() {
  
	char16_t echo;
	String command;

	if (Serial.available()) {
		command = Serial.readString();
		for (int i = 0; i < command.length(); i++) {
			Serial.write(command[i]);
		}
	}

	delay(1000);

	while (Serial.available()) {
		Serial.println(Serial.read());
	}

}
