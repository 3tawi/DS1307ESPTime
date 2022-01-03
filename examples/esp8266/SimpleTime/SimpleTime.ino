//  DS1307ESPTime Edited by 3tawi
//  DS1307ESPTime Library: https://github.com/3tawi/DS1307ESPTime
//  Find All "Great Projects" Videos : https://www.youtube.com/c/GreatProjects

#include <DS1307ESPTime.h>

DS1307ESPTime rtc;

void setup() {
  Serial.begin(115200);
  rtc.setTime(30, 58, 19, 13, 1, 2022);  // 13 Jan 2022 19:58:30
  //rtc.setTime(1610897079);  // 13 Jan 2022 00:00:00
}
void loop() {
  Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));   // (String) returns time with specified format 
// formating options  http://www.cplusplus.com/reference/ctime/strftime/
  
//  Serial.println(rtc.getTime());          //  (String) 19:58:30
//  Serial.println(rtc.getDate());          //  (String) Sun, Jan 13 2022
//  Serial.println(rtc.getDate(true));      //  (String) Sunday, January 13 2022
//  Serial.println(rtc.getDateTime());      //  (String) Sun, Jan 13 2021 19:58:30
//  Serial.println(rtc.getDateTime(true));  //  (String) Sunday, January 13 2022 19:58:30
//  Serial.println(rtc.getTimeDate());      //  (String) 19:58:30 Sun, Jan 13 2022
//  Serial.println(rtc.getTimeDate(true));  //  (String) 19:58:30 Sunday, January 13 2022
//
//  Serial.println(rtc.getMicros());        //  (long)    684822
//  Serial.println(rtc.getMillis());        //  (long)    684
//  Serial.println(rtc.getEpoch());         //  (long)    1610897079
//  Serial.println(rtc.getSecond());        //  (int)     56    (0-59)
//  Serial.println(rtc.getMinute());        //  (int)     33    (0-59)
//  Serial.println(rtc.getHour());          //  (int)     2     (0-12)
//  Serial.println(rtc.getHour(true));      //  (int)     22    (0-23)
//  Serial.println(rtc.getAmPm());          //  (String)  pm
//  Serial.println(rtc.getAmPm(true));      //  (String)  PM
//  Serial.println(rtc.getDay());           //  (int)     13    (1-31)
//  Serial.println(rtc.getDayofWeek());     //  (int)     2     (0-6)
//  Serial.println(rtc.getDayofYear());     //  (int)     28    (0-365)
//  Serial.println(rtc.getMonth());         //  (int)     3     (0-11)
//  Serial.println(rtc.getYear());          //  (int)     2022
  
  delay(1000);
}
