#include <ESP8266WiFi.h> //LIBLARY
IPAddress local_IP(192,168,5,25); //LOCAL IP
IPAddress subnet(255,255,255,0); //SUBNET
IPAddress gateway(192,168,5,1); //GATEWAY

void setup(){
  Serial.begin(115200); //SERIAL INIT
  pinMode(2, OUTPUT); //PORT 2 -> ESP8266 LED
  WiFi.softAPConfig(local_IP, gateway, subnet); //CONFIG
  WiFi.softAP("ESP8266WIFI", "123456789", 1, false, 6); //NAME AND PASSWORD
  Serial.println(WiFi.softAPIP()); // -> IP
  
  
}
void loop() {
  delay(400); //JUST FOR TEST
  digitalWrite(2, HIGH); //JUST FOR TEST!!
}
