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

// ---- Time ----
String TIME_timeToWeekday(time_t datetime);
void TIME_timeToString(time_t timeValue, char* timeString, size_t bufferSize);
bool TIME_isSameDay(time_t time1, time_t time2);

// ---- Text ----
const char *TEXT_getWiFidesc(int rssi);

const char *TEXT_getAQIdesc(int aqi);