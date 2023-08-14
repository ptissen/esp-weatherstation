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

#include "timehandler.h"

#include "config/config.h"
#include "logging.h"

void TimeHandler::ini()
{
  configTime(TIME_GMT_OFFSET_SEC, TIME_DAYLIGHTOFFSET, TIME_NTP_SERVER1, TIME_NTP_SERVER2);
}

void TimeHandler::update()
{
  logI.println("\n------------ Time ------------");
  logD.print("  Fetch Time : ");

  for (int i = 0; i < TIME_MAX_TRY; i++) {
    logD.print(".");

    if (getLocalTime(&m_lastUpdate)) {
      logD.println(" sucess");
      m_isTimeValid = true;
      break;
    }
    else{
      delay(1000);
    }
  }

  if (!m_isTimeValid) {
    logD.println(" failed");
    return;
  }
  logD.println(&m_lastUpdate, "  Datetime: %d.%m.%Y %X");
}