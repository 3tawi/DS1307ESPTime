//  DS1307ESPTime Edited by 3tawi
// - DS1307ESPTime Library: https://github.com/3tawi/DS1307ESPTime
// Find All "Great Projects" Videos : https://www.youtube.com/c/GreatProjects


#include <WiFi.h>
#include <WebServer.h>
#include <DS1307ESPTime.h>
#include "index.h"

DS1307ESPTime rtc;
WebServer server(80);

char ssid[] = "your-ssid";
char pass[] = "your-password";
const char* Apssid = "Espxx";
const char* Appassword = "3tawi-GP";
  IPAddress ip(192,168,1,142);
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
    WiFi.softAP(Apssid, Appassword);
    Serial.println("CONNECTED To: NeoPixel");
    Serial.println("Password: '3tawi-GP'");
    Serial.print("IP Address: http://");
    Serial.println(WiFi.softAPIP().toString().c_str());
    }
}
  void handleRoot() {
 server.send(200, "text/html", MAIN_page); //Send web page
}
void handlesaveTime() { 
    handleRoot();
    writeTime();
    Serial.println("Time Saved"); 
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
    String hbuf = server.arg("htmie"); 
    String dbuf = server.arg("ddate");
    text = hbuf[0];
    text += hbuf[1];
    int h = text.toInt(); 
    text = hbuf[3];
    text += hbuf[4];
    int m = text.toInt(); 
    text = hbuf[6];
    text += hbuf[7];
    int s = text.toInt();
    
    text = dbuf[0];
    text += dbuf[1];
    text += dbuf[2];
    text += dbuf[3];
    int yr = text.toInt(); 
    text = dbuf[5];
    text += dbuf[6];
    int mo = text.toInt();
    text = dbuf[8];
    text += dbuf[9];
    int dd = text.toInt();
    rtc.setTime(s, m, h, dd, mo, yr);
    Serial.println("Manually Time Update ");
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
  getWifi(); 
  rtc.begin(); 
  updateTime();
  server.on("/", handleRoot); 
  server.on("/ntptime", handlentpTime); 
  server.on("/mytimezon", handlezoneTime); 
  server.on("/localdatime", handlelocaltime);
  server.on("/restime", handleMyTime);
  server.on("/readtemhu", handlestate);  
  server.on("/savetime", handlesaveTime); 
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
void updateTime()
{
  configTime(0, 0, "", "");
  rtc.DSgetTime(); 
  int dd = rtc.dayOfMonth, mo = rtc.month + 1, yr = rtc.year + 2000;
  rtc.setTime(rtc.second, rtc.minute, rtc.hour, dd, mo, yr);
  configTime(Tz * 3600, 0, "", "");
} 
void writeTime()
{
  configTime(0, 0, "", ""); 
  int h = rtc.getHour(true), m = rtc.getMinute(), s = rtc.getSecond(),
      yr = rtc.getYear(), mo = rtc.getMonth(), dd = rtc.getDay(),
      dw = rtc.getDayofWeek();
  rtc.datime(h, m, s, yr, mo, dd, dw); 
  rtc.DSsetTime(); 
  configTime(Tz * 3600, 0, "", "");
}
