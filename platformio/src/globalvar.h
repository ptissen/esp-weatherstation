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

#pragma once

#include <Arduino.h>
#include <WiFi.h>

extern RTC_DATA_ATTR int SYS_BOOT_COUNT;

extern int GL_BAT_PERCENTAGE;
extern float GL_BAT_VOLTAGE;
extern int GL_WIFI_DBM;
extern struct tm* GL_TIME_LASTUPDATE;
extern String GL_STATUS;
extern bool GL_IS_ERROR;

extern WiFiClient m_client;
