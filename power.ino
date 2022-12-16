#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "powerdistributionsystem-2c054-default-rtdb.firebaseio.com"  //Database link
#define FIREBASE_AUTH "jOZD3FUhnshTxeH0JwFowlfGEHaJJlHp0G3H5Sp0"  //Database secrate

#define WIFI_SSID "SmartPower"      //Router name
#define WIFI_PASSWORD "123456789"  //Router password



FirebaseData firebaseData,loadData;
FirebaseJson json;



//Sending data
void loadW(String field,int value){
 Firebase.setString(firebaseData, "/Load/"+field,String(value) );
  
}

//Receiving data
String loadR(String field){
if (Firebase.getString(loadData, "/Load/"+field)){
    return loadData.stringData();
  }
}



void initFire(){
  pinMode(D4,OUTPUT);
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(D4,0);
    Serial.print(".");
    delay(200);
    digitalWrite(D4,1);
    Serial.print(".");
    delay(200);
    
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}














void setup() {

  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D5,INPUT);
  Serial.begin(9600);
  initFire();

  delay(500);

  Firebase.setString(firebaseData, "/Hello","World" );

  
   

}




void loop() {

  digitalWrite(D0,loadR("220 volt - 110 volt")=="1");
  delay(250);
  digitalWrite(D1,loadR("110 volt - 55 volt")=="1");
  delay(250);
  digitalWrite(D2,loadR("55 volt - 24 volt")=="1");
  delay(250);
  digitalWrite(D3,loadR("24 volt - 12 volt")=="1");
  delay(250);

}