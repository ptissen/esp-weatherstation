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
#include <Adafruit_GFX.h>

#include "openweathermap.h"

class DisplayHandler
{
public:
    /***
     * Aligments:
        LT       CT       RT
            +-----------+
            |           |
        LC  |    CC     | RC
            |           |
            +-----------+
        LB      CB        RB

    */
    typedef enum
    {
        ALIGN_LT,
        ALIGN_LC,
        ALIGN_LB,
        
        ALIGN_CT,
        ALIGN_CC,
        ALIGN_CB,
        
        ALIGN_RT,
        ALIGN_RC,
        ALIGN_RB
    } ALIGN_t;

    typedef enum
    {
        ERR_NOT,
        ERR_BATTERY,
        ERR_WIFI,
        ERR_API,
        ERR_TIME,
        ERR_SYSTEM

    } ERROR_t;

    DisplayHandler(void) = default;

    void update(const OpenWeatherMap &owm);
    void drawError(ERROR_t err);
    bool isInit();

private:

    void ini();
    void off();
    
    void drawWeatherCurrent(const OpenWeatherMap::owm_current_weather_t &owm);
    void drawForecastDays(const OpenWeatherMap::owm_daily_t &owm);
    void drawWeatherInfos(const OpenWeatherMap::owm_current_weather_t &owm, const OpenWeatherMap::owm_air_pollution_t &owm_ap);
    void drawWeatherGraph(const OpenWeatherMap::owm_current_weather_t &owm, const OpenWeatherMap::owm_air_pollution_t &owm_ap);
    void drawStatusBar();
    void drawForecastGraph(const OpenWeatherMap::owm_5_days_forecast_t &owm);

    bool m_isInit = false;

    void drawText(int16_t x0, int16_t y0, String text, ALIGN_t align);

    uint16_t getTextWidth(String text);

};