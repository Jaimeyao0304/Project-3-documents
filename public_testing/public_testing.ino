/*
  Rui Santos
  Complete project details at our blog.
    - ESP32: https://RandomNerdTutorials.com/esp32-firebase-realtime-database/
    - ESP8266: https://RandomNerdTutorials.com/esp8266-nodemcu-firebase-realtime-database/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  Based in the RTDB Basic Example by Firebase-ESP-Client library by mobizt
  https://github.com/mobizt/Firebase-ESP-Client/blob/main/examples/RTDB/Basic/Basic.ino
*/

#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "ACCD"
#define WIFI_PASSWORD "tink1930"

// Insert Firebase project API Key
#define API_KEY "AIzaSyACi2zN89w-9RoAZdFg5fJSm2dJrFbJuJc"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://pubsub-test-f5f3d-default-rtdb.firebaseio.com/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
const int potPin = 39;

//int count = 0;
bool signupOK = false;

int potValue;
int sendvalue;
int intValue;

float voltage = 0;

void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){
//  int xx;
//  xx = analogRead(A3);
// Serial.println(xx);
//  delay(1000);
//    
  
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    potValue = analogRead(A3);
    sendvalue = potValue;

    
//    voltage = (3.3/4095.0) * potValue;
  
      
    if (Firebase.RTDB.setInt(&fbdo, "JaimeDatabase/int", sendvalue)){
 //   Serial.println("PASSED");
//    Serial.println(potValue);
//    Serial.println("PATH: " + fbdo.dataPath());
//    Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    if (Firebase.RTDB.getInt(&fbdo, "/Node_A/int")) {
      if (fbdo.dataType() == "int") {
        intValue = fbdo.intData();
        Serial.println(intValue);        
      }
    }
//    if (Firebase.RTDB.getInt(&fbdo, "/Node_B/int")) {
//      if (fbdo.dataType() == "int") {
//        intValue = fbdo.intData();
//        Serial.println(intValue);       
//      }
//    }
    //count++;
    
//            // Write an Float number on the database path test/float
//            if (Firebase.RTDB.setFloat(&fbdo, "JaimeDatabase/float", voltage)){
//              Serial.println("PASSED");
//              Serial.println(voltage);
//              Serial.println("PATH: " + fbdo.dataPath());
//              Serial.println("TYPE: " + fbdo.dataType());
//            }
//    else {
//      Serial.println("FAILED");
//      Serial.println("REASON: " + fbdo.errorReason());
//    }
    
  }
}
