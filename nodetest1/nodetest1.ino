
/*
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2020 mobizt
 * 
 * This example is for FirebaseESP8266 Arduino library v 2.8.9 or later
 *
*/

//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "nodemcu-test-4a5ee-default-rtdb.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "fUjT7yeuwQ3W16LaweAI1h41g9h0f4MB7fJ4UCdS"
#define WIFI_SSID "bhaikakhauf"
#define WIFI_PASSWORD "12345678"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

FirebaseJson json;

void setup()
{

  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  firebaseData.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  firebaseData.setResponseSize(1024);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  //optional, set the decimal places for float and double data to be stored in database
  Firebase.setFloatDigits(2);
  Firebase.setDoubleDigits(6);
}

void loop()
{

  if (Firebase.getInt(firebaseData, "/test1")) {

    if (firebaseData.dataType() == "int") {
      Serial.println(firebaseData.intData());

      if(firebaseData.intData()==1){
          digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(1000); 
        }
      else{
         digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
          delay(1000);                       
        }

 
      
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }
  
}
