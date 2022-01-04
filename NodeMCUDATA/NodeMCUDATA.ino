/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

SoftwareSerial uno(D1,D2);
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "vX1QY3s8gLML1e9U924pubOSCk61TWPw";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SametC";
char pass[] = "1234samet";

int speedo;
int rpmFromUno;
int coolantTemp;
void setup()
{
  // Debug console
  Serial.begin(115200);
  uno.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
}

void loop()
{

  if(uno.available()){
    rpmFromUno=uno.read();
    if(rpmFromUno>=650 && rpmFromUno<=6500){
    Blynk.virtualWrite(V1, rpmFromUno);
    Serial.println(rpmFromUno);
    Serial.println("yokuz");
  }}
  else("not available");
  
  Blynk.run();
  
  //Blynk.virtualWrite(V1,rpmFromUno);
  Blynk.virtualWrite(V2,speedo);
  Blynk.virtualWrite(V3,coolantTemp);
 
}
