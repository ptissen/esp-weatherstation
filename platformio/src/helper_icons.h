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
#include "../icons/icons.h"

class ICONS {
public:
    static const uint8_t *getBattery24(int percent);
    static const uint8_t *getWifi16(int dbm);
    static const uint8_t *getWeather64(int id, bool isNight);
    static const uint8_t *getWeather160(int id, bool isNight);
    static const uint8_t *getMoonPhase24();
    //static const uint8_t *getWindDeg24(int windDegrees);
    static const uint8_t *getWindBeaufort48(int beaufort);
};