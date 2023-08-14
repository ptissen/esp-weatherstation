/*
 *   This file belongs to the Project ESP-WeatherStation
 *   Copyright (c) 2023 Peter Tißen, Stephan Brüning
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "helper.h"

#include "locale/locale_de.h"

String TIME_timeToWeekday(time_t datetime){

    time_t t = (time_t) datetime;
    struct tm* timeinfo;
    timeinfo = localtime(&t);

    return LC_DAY_AB[timeinfo->tm_wday];
}

void TIME_timeToString(time_t timeValue,char* timeString, size_t bufferSize) {
  struct tm* timeinfo;
  timeinfo = localtime(&timeValue);
  
  strftime(timeString, bufferSize, "%H:%M", timeinfo);
}

bool TIME_isSameDay(time_t time1, time_t time2) {
    struct tm timeinfo1;
    struct tm timeinfo2;
    gmtime_r(&time1, &timeinfo1);
    gmtime_r(&time2, &timeinfo2);

    return (timeinfo1.tm_mday == timeinfo2.tm_mday &&
            timeinfo1.tm_mon == timeinfo2.tm_mon &&
            timeinfo1.tm_year == timeinfo2.tm_year);
}

const char *TEXT_getWiFidesc(int rssi)
{
  if (rssi == 0)            return TXT_WIFI_NO_CONNECTION;
  else if (rssi >= -50)     return TXT_WIFI_EXCELLENT;
  else if (rssi >= -60)     return TXT_WIFI_GOOD;
  else if (rssi >= -70)     return TXT_WIFI_FAIR;
  else                      return TXT_WIFI_WEAK;
}

const char *TEXT_getAQIdesc(int aqi){

  switch (aqi)
  {
  case 1: return "Sehr Gut";
  case 2: return "Gut";
  case 3: return "Ok";
  case 4: return "Schlecht";
  case 5: return "Horrend";
  }

    return "Unknown";
}