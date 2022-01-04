
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

SoftwareSerial uno(D1,D2);
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
