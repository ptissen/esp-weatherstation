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

#include "battery.h"
#include "wifihandler.h"
#include "timehandler.h"
#include "openweathermap.h"
#include "displayhandler.h"
#include "handler_mqtt.h"

class WeatherStation {
public:
    WeatherStation(void){}

    void ini();
    void testDisplay();

private:
    bool isBootReasonOk();
    void activateDeepSleep(bool forever, TimeHandler &t);

    OpenWeatherMap m_owm;
    
    Battery m_battery;
    WifiHandler m_wifiHandler;
    TimeHandler m_timeHandler;
    DisplayHandler m_displayHandler;
};