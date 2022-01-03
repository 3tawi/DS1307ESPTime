/*
   MIT License

  Copyright (c) 2021 3tawi

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


#ifndef DS1307ESPTime_H
#define DS1307ESPTime_H

#include <Arduino.h>

#define DS1307_I2C_ADDRESS 0x68

class DS1307ESPTime {
       private:
               uint8_t decToBcd(uint8_t val);
               uint8_t bcdToDec(uint8_t val);
	
	public:
		DS1307ESPTime();
		void setTime(long epoch = 1609459200, int ms = 0);	// default (1609459200) = 1st Jan 2021
		void setTime(int sc, int mn, int hr, int dy, int mt, int yr, int ms = 0);
		void getTimeStruct();
		String getTime(String format);
		void begin();
		void DSsetTime();
		void DSgetTime();
		void datime(uint8_t _hour, uint8_t _minute, uint8_t _second, uint16_t _year, uint8_t _month, uint8_t _day, uint8_t _dow);
		uint8_t second;
		uint8_t minute;
		uint8_t hour;
		uint8_t dayOfWeek;// day of week, 1 = Monday
		uint8_t dayOfMonth;
		uint8_t month;
		uint16_t year;
		
		String getTime();
		String getDateTime(bool mode = false);
		String getTimeDate(bool mode = false);
		String getDate(bool mode = false);
		String getAmPm(bool lowercase = false);
		
		long getEpoch();
		long getMillis();
		long getMicros();
		int getSecond();
		int getMinute();
		int getHour(bool mode = false);
		int getDay();
		int getDayofWeek();
		int getDayofYear();
		int getMonth();
		int getYear();
		

};

#endif


