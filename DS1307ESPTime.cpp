/*
   MIT License

  Copyright (c) 2022 3tawi

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "DS1307ESPTime.h"
#include <Wire.h>
#include <time.h>                       // time() ctime()
#include <sys/time.h>                   // struct timeval

time_t now;

/*!
    @brief  Constructor for ESP8266Time
*/
DS1307ESPTime::DS1307ESPTime(){}

/*!
    @brief  set the internal RTC time
    @param  sc
            second (0-59)
    @param  mn
            minute (0-59)
    @param  hr
            hour of day (0-23)
    @param  dy
            day of month (1-31)
    @param  mt
            month (1-12)
    @param  yr
            year ie 2021
    @param  ms
            microseconds (optional)
*/
void DS1307ESPTime::setTime(int sc, int mn, int hr, int dy, int mt, int yr, int ms) {
  // seconds, minute, hour, day, month, year $ microseconds(optional)
  // ie setTime(20, 54, 13, 1, 1, 2022) = 13:54:20 1/1/2022
  struct tm t = {0};        // Initalize to all 0's
  t.tm_year = yr - 1900;    // This is year-1900, so 122 = 2022
  t.tm_mon = mt - 1;
  t.tm_mday = dy;
  t.tm_hour = hr;
  t.tm_min = mn;
  t.tm_sec = sc;
  time_t timeSinceEpoch = mktime(&t);
  setTime(timeSinceEpoch, ms);
}

/*!
    @brief  set the internal RTC time
    @param  epoch
            epoch time in seconds
    @param  ms
            microseconds (optional)
*/
void DS1307ESPTime::setTime(long epoch, int ms) {
  struct timeval tv;
  tv.tv_sec = epoch;  // epoch time (seconds)
  tv.tv_usec = ms;    // microseconds
  settimeofday(&tv, NULL);
}

/*!
    @brief  get the internal RTC time as a tm struct
*/
void DS1307ESPTime::getTimeStruct(){
 struct timeval tv;
  gettimeofday(&tv, nullptr);
  now = time(nullptr);
}

/*!
    @brief  get the time and date as an Arduino String object
    @param  mode
            true = Long date format
			false = Short date format
*/
String DS1307ESPTime::getDateTime(bool mode){
	getTimeStruct();
	struct tm* timeinfo = localtime(&now);
	char s[51];
	if (mode)
	{
		strftime(s, 50, "%A, %B %d %Y %H:%M:%S", timeinfo);
	}
	else
	{
		strftime(s, 50, "%a, %b %d %Y %H:%M:%S", timeinfo);
	}
	return String(s);
}

/*!
    @brief  get the time and date as an Arduino String object
    @param  mode
            true = Long date format
			false = Short date format
*/
String DS1307ESPTime::getTimeDate(bool mode){
	getTimeStruct();
	struct tm* timeinfo = localtime(&now);
	char s[51];
	if (mode)
	{
		strftime(s, 50, "%H:%M:%S %A, %B %d %Y", timeinfo);
	}
	else
	{
		strftime(s, 50, "%H:%M:%S %a, %b %d %Y", timeinfo);
	}
	return String(s);
}

/*!
    @brief  get the time as an Arduino String object
*/
String DS1307ESPTime::getTime(){
	getTimeStruct();
	struct tm* timeinfo = localtime(&now);
	char s[51];
	strftime(s, 50, "%H:%M:%S", timeinfo);
	return String(s);
}

/*!
    @brief  get the time as an Arduino String object with the specified format
	@param	format
			time format 
			http://www.cplusplus.com/reference/ctime/strftime/
*/
String DS1307ESPTime::getTime(String format){
	getTimeStruct();
	struct tm* timeinfo = localtime(&now);
	char s[128];
	char c[128];
	format.toCharArray(c, 127);
	strftime(s, 127, c, timeinfo);
	return String(s);
}

/*!
    @brief  get the date as an Arduino String object
    @param  mode
            true = Long date format
			false = Short date format
*/
String DS1307ESPTime::getDate(bool mode){
	getTimeStruct();
	struct tm* timeinfo = localtime(&now);
	char s[51];
	if (mode)
	{
		strftime(s, 50, "%A, %B %d %Y", timeinfo);
	}
	else
	{
		strftime(s, 50, "%a, %b %d %Y", timeinfo);
	}
	return String(s);
}

/*!
    @brief  get the current milliseconds as long
*/
long DS1307ESPTime::getMillis(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_usec/1000;
}

/*!
    @brief  get the current microseconds as long
*/
long DS1307ESPTime::getMicros(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_usec;
}

/*!
    @brief  get the current epoch seconds as long
*/
long DS1307ESPTime::getEpoch(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec;
}

/*!
    @brief  get the current seconds as int
*/
int DS1307ESPTime::getSecond(){
	getTimeStruct();
	struct tm* p_tm = localtime(&now);
	return p_tm->tm_sec;
}

/*!
    @brief  get the current minutes as int
*/
int DS1307ESPTime::getMinute(){
	getTimeStruct();
	struct tm* p_tm = localtime(&now);
	return p_tm->tm_min;
}

/*!
    @brief  get the current hour as int
	@param	mode
			true = 24 hour mode (0-23)
			false = 12 hour mode (0-12)
*/
int DS1307ESPTime::getHour(bool mode){
	getTimeStruct();
	struct tm* p_tm = localtime(&now);
	if (mode)
	{
		return p_tm->tm_hour;
	}
	else
	{
		int hour = p_tm->tm_hour;
		if (hour > 12)
		{
			return p_tm->tm_hour-12;
		}
		else
		{
			return p_tm->tm_hour;
		}
		
	}
}

/*!
    @brief  return current hour am or pm
	@param	lowercase
			true = lowercase
			false = uppercase
*/
String DS1307ESPTime::getAmPm(bool lowercase){
	getTimeStruct();
	struct tm* p_tm = localtime(&now);
	if (p_tm->tm_hour >= 12)
	{
		if (lowercase)
		{
			return "pm";
		}
		else
		{
			return "PM";
		}
	}
	else
	{
		if (lowercase)
		{
			return "am";
		}
		else
		{
			return "AM";
		}
	}
}

/*!
    @brief  get the current day as int (1-31)
*/
int DS1307ESPTime::getDay(){
	getTimeStruct();
	struct tm* p_tm = localtime(&now);
	return p_tm->tm_mday;
}

/*!
    @brief  get the current day of week as int (0-6)
*/
int DS1307ESPTime::getDayofWeek(){
	getTimeStruct();
	struct tm* p_tm = localtime(&now);
	return p_tm->tm_wday;
}

/*!
    @brief  get the current day of year as int (0-365)
*/
int DS1307ESPTime::getDayofYear(){
	getTimeStruct();
	struct tm* p_tm = localtime(&now);
	return p_tm->tm_yday;
}

/*!
    @brief  get the current month as int (0-11)
*/
int DS1307ESPTime::getMonth(){
	getTimeStruct();
	struct tm* p_tm = localtime(&now);
	return p_tm->tm_mon;
}

/*!
    @brief  get the current year as int
*/
int DS1307ESPTime::getYear(){
	getTimeStruct();
	struct tm* p_tm = localtime(&now);
	return p_tm->tm_year+1900;
}

void DS1307ESPTime::DSbegin() {
    Wire.begin();
}

uint8_t DS1307ESPTime::decToBcd(uint8_t val) {
    return ((val / 10 * 16) + (val % 10));
}

uint8_t DS1307ESPTime::bcdToDec(uint8_t val) {
    return ((val / 16 * 10) + (val % 16));
}

void DS1307ESPTime::DSgetdatime() {
    // Reset the register pointer
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();
    Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
    // A few of these need masks because certain bits are control bits
    second     = bcdToDec(Wire.read() & 0x7f);
    minute     = bcdToDec(Wire.read());
    hour       = bcdToDec(Wire.read() & 0x3f);// Need to change this if 12 hour am/pm
    dayOfWeek  = bcdToDec(Wire.read());
    dayOfMonth = bcdToDec(Wire.read());
    month      = bcdToDec(Wire.read());
    year       = bcdToDec(Wire.read());
    setTime(second, minute, hour, dayOfMonth, month+1, year+2000);
}

void DS1307ESPTime::DSsetTime() {
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.write(decToBcd(second));// 0 to bit 7 starts the clock
    Wire.write(decToBcd(minute));
    Wire.write(decToBcd(hour));  // If you want 12 hour am/pm you need to set bit 6
    Wire.write(decToBcd(dayOfWeek));
    Wire.write(decToBcd(dayOfMonth));
    Wire.write(decToBcd(month));
    Wire.write(decToBcd(year));
    Wire.endTransmission();
}

void DS1307ESPTime::DSsetdatime() {
    hour = getHour(true);
    minute = getMinute();
    second = getSecond();
    year = getYear() - 2000;
    month = getMonth();
    dayOfMonth = getDay();
    dayOfWeek = getDayofWeek();
    DSsetTime();
}