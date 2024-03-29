//  DS1307ESPTime Edited by 3tawi
//  DS1307ESPTime Library: https://github.com/3tawi/DS1307ESPTime
//  Find All "Great Projects" Videos : https://www.youtube.com/c/GreatProjects

#include <WiFi.h>
#include <WebServer.h>
#include <DS1307ESPTime.h>
#include "index.h"

DS1307ESPTime rtc;
WebServer server(80);

char ssid[] = "your-ssid";
char pass[] = "your-password";
const char* Apssid = "DS1307";
const char* Appassword = "3tawi-GP";
  IPAddress ip(192,168,1,31);
  IPAddress dns(192, 168,1,1);
  IPAddress gateway(192, 168,1,1);
  IPAddress gatewayap(192,168,4,1);
  IPAddress subnet(255, 255, 255, 0);

uint32_t lastTime;   
int Tz = 1; // Time Zone
String text;

void(* resetFunc) (void) = 0;//declare reset function at address 0

void getWifi() {
  WiFi.config(ip, dns, gateway, subnet); 
  WiFi.begin(ssid, pass);
  int xc = 0;
  while (WiFi.status() != WL_CONNECTED && xc < 10) {
    delay(500);
    xc++;
  }
  if (WiFi.status() == WL_CONNECTED) { 
    Serial.print("CONNECTED To: ");
    Serial.println(ssid);
    Serial.print("IP Address: http://");
    Serial.println(WiFi.localIP().toString().c_str());
    WiFi.softAPdisconnect(true);
    } else { 
    WiFi.softAPConfig(ip, gatewayap, subnet);
    WiFi.softAP(Apssid, Appassword);
    Serial.print("CONNECTED To: ");
    Serial.print(Apssid);
    Serial.print(" Password: ");
    Serial.println(Appassword);
    Serial.print("IP Address: http://");
    Serial.println(WiFi.softAPIP().toString().c_str());
    }
}
  void handleRoot() {
 server.send(200, "text/html", MAIN_page); //Send web page
}
void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
    Serial.println("NTP Time Update ");
}
void handlentpTime() {
  handleRoot();
  configTime(Tz * 3600, 3600, "145.238.203.10", "145.238.203.14");
  printLocalTime();
}
void handlezoneTime() {
    handleRoot();
    Tz = server.arg("locatz").toInt(); 
    configTime(Tz * 3600, 0, "", "");
    Serial.println("Zone Time Update ");
}
void handlelocaltime() { 
    handleRoot();
    rtc.setTime(server.arg("locadt").toInt());  
    configTime(Tz * 3600, 0, "", "");
    Serial.println("Local Time Update ");
}
void handleMyTime() { 
    handleRoot();
    int hh = server.arg("htmie").toInt();
    int mm = server.arg("mtmie").toInt();
    int ss = server.arg("stmie").toInt();
    int dd = server.arg("ddate").toInt();
    int mo = server.arg("mdate").toInt();
    int yr = server.arg("ydate").toInt();
    rtc.setTime(ss, mm, hh, dd, mo, yr);
}
void handlestate() {
  String content = "<?xml version = \"1.0\" ?>";
  content += "<inputs><analog>";
  content += Tz;
  content += "</analog></inputs>";
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "text/xml", content); //Send web page
}
void handleRestesp() {  
    handleRoot();
    delay(4000);     
    resetFunc();
}
void setup() {
  Serial.begin(115200);
  rtc.setTime(30, 58, 19, 1, 1, 2022);  // 1th Jan 2022 19:58:30
  //rtc.setTime(1610897079);  // 1st Jan 2022 00:00:00
  getWifi();
  server.on("/", handleRoot); 
  server.on("/ntptime", handlentpTime); 
  server.on("/mytimezon", handlezoneTime); 
  server.on("/localdatime", handlelocaltime);
  server.on("/mydtime", handleMyTime);
  server.on("/readtemhu", handlestate);
  server.on("/restesp", handleRestesp);
  server.begin(); 
}
void loop() {

  server.handleClient();
   if(millis() - lastTime >= 1000) {
  Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));   // (String) returns time with specified format 
  //struct tm timeinfo;
  //if(getLocalTime(&timeinfo)){
  //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  //}
      lastTime = millis();
    }
}
