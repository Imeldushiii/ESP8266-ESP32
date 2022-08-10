#include <ESP8266WiFi.h>
const char* ssid = "Twoje SSID ";
const char* password = "Twoje Haslo do SSID";
WiFiServer server(80);
String header;
String output1 = "off";
String output2 = "off";
String output3 = "off";
String output4 = "off";
String output5 = "off";
const int D1 = 5;
const int D2 = 4;
const int D3 = 0;
const int D4 = 2;
const int D5 = 14;

void setup() {
Serial.begin(115200);
pinMode(D1, OUTPUT);
pinMode(D2, OUTPUT);
pinMode(D3, OUTPUT);
pinMode(D4, OUTPUT);
pinMode(D5, OUTPUT);
digitalWrite(D1, LOW);
digitalWrite(D2, LOW);
digitalWrite(D3, LOW);
digitalWrite(D4, LOW);
digitalWrite(D5, LOW);

WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
}
server.begin();
}

void loop(){
WiFiClient client = server.available(); 

if (client) { 
String currentLine = ""; 

while (client.connected()) { 

if (client.available()) { 
char c = client.read(); 
Serial.write(c); 
header += c;
if (c == '\n') { 

if (currentLine.length() == 0) {
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println();


if (header.indexOf("GET /1/on") >= 0) {
output1 = "on";
digitalWrite(D1, HIGH);
}

else if (header.indexOf("GET /1/off") >= 0) {

output1 = "off";
digitalWrite(D1, LOW);
} else if (header.indexOf("GET /2/on") >= 0) {
output2 = "on";
digitalWrite(D2, HIGH);
} else if (header.indexOf("GET /2/off") >= 0) {
output2 = "off";
digitalWrite(D2, LOW);
} else if (header.indexOf("GET /3/on") >= 0) {
output3 = "on";
digitalWrite(D3, HIGH);
}

else if (header.indexOf("GET /3/off") >= 0) {
Serial.println("Yellow LED is off");
output3 = "off";
digitalWrite(D3, LOW);
} 
else if (header.indexOf("GET /4/on") >= 0) {
  output4 = "on";
  digitalWrite(D4, HIGH);
}
else if (header.indexOf("GET /4/off") >= 0) {
  output4 = "off";
  digitalWrite(D4, LOW);
}
else if (header.indexOf("GET /5/on") >= 0) {
  output5 = "on";
  digitalWrite(D5, HIGH);
  
}
else if (header.indexOf("GET /5/off") >= 0) {
  output5 = "off";
  digitalWrite(D5, LOW);
}



client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");

client.println("<style>");
client.println("* {margin:0; padding: 0; font-family: arial;}");
client.println(".container { width: 100%; height: 100vh;  display: flex; align-items: center;justify-content: center; flex-direction: column;}");
client.println(".clickoff {width:200px; height: 50px; background: red; font-size: 15px; margin: 10px;}");
client.println(".clickon {width:200px; height: 50px; background: green; font-size: 15px; margin: 10px;}");
client.println("</style></head>");

client.println("<body><div class=\"container\"> <h1>Kontrolowanie Pinow D1 - D5</h1>");
if (output1 == "off") {
  client.println("<a href=\"/1/on\"><button class=\"clickon\">D1 - Wlacz</button></a>");
}
else {
  client.println("<a href=\"/1/off\"><button class=\"clickoff\">D1 - Wylacz</button></a>");
}
if (output2 == "off") {
  client.println("<a href=\"/2/on\"><button class=\"clickon\">D2 - Wlacz</button></a>");
}
else {
  client.println("<a href=\"/2/off\"><button class=\"clickoff\">D2 - Wylacz</button></a>");
}
if (output3 == "off") {
  client.println("<a href=\"/3/on\"><button class=\"clickon\">D3 - Wlacz</button></a>");
}
else {
  client.println("<a href=\"/3/off\"><button class=\"clickoff\">D3 -Wylacz</button></a>");
}

if (output4 == "off") {
  client.println("<a href=\"/4/on\"><button class=\"clickon\">D4 - Wlacz</button></a>");
}
else {
  client.println("<a href=\"/4/off\"><button class=\"clickoff\">D4 - Wylacz</button></a>");
}
if (output5 == "off") {
  client.println("<a href=\"/5/on\"><button class=\"clickon\">D5 - Wlacz</button></a>");
}
else {
  client.println("<a href=\"/5/off\"><button class=\"clickoff\">D5 - Wylacz</button></a>");
}
client.println("</div></body></html>");

client.println();

break;
} else { 
currentLine = "";
}
} else if (c != '\r') { 
currentLine += c; 
}
}

header = "";

client.stop();
Serial.println("Client disconnected.");
Serial.println("");
}
}
