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

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

#include <cstdint>
#include <vector>

class OpenWeatherMap {

public:
    // Current Weather Data
    typedef struct {
        struct {
            int id;
            char icon[5];
        } weather;
        struct {
            float temp;
            float feels_like;
            float temp_min;
            float temp_max;
            int pressure;
            int humidity;
            int sea_level;
            int grnd_level;
        } main;
        struct {
            float speed;
            int deg;
            float gust;
        } wind;
        struct {
            float h1;
        } rain;
        int dt;
        struct {
            int sunrise;
            int sunset;
        } sys;
    } owm_current_weather_t;

    // 5 Days Weather forecast
    typedef struct {
        struct {
            int dt;
            struct {
                float temp;
                float feels_like;
                float temp_min;
                float temp_max;
                int pressure;
                int humidity;
                float temp_kf;
            } main;
            struct {
                int id;
                char icon[5];
            } weather;
            struct {
                float speed;
                int deg;
                float gust;
            } wind;
            float pop;
            struct {
                float h3;
            } rain;
        } list[40];
    } owm_5_days_forecast_t;

    // Air Pollution
    typedef struct {
        struct {
            int dt;
            struct {
                float aqi;
            } main;
            struct {
                float co;
                float no;
                float no2;
                float o3;
                float so2;
                float pm2_5;
                float pm10;
                float nh3;
            } components;
        } list[1];
    } owm_air_pollution_t;

    typedef struct owm_daily
    {
        struct {
            int dt;
            int temp_min;
            int temp_max;
            int rain;
            int id;
            int dataCount;
        }day[6];
    } owm_daily_t;

    enum class WEATHER_DATA_TYPE
    {
        Current,
        Forecast,
        AirQuality
    };

    OpenWeatherMap(void) {};

    void update();

    bool isError() { return m_isError; }

    owm_current_weather_t m_cwd;
    owm_5_days_forecast_t m_5df;
    owm_air_pollution_t m_ap;
    owm_daily_t m_daily;

private:
    bool m_isError = false;
    bool m_isDataValid = false;
    int m_errorCode = 0;
    
    void getCurrentWeather();
    void get5DayForcast();
    void getAirPollution();

    void fetchWeatherData(const WEATHER_DATA_TYPE dataType);

    void convert5DayToDaily();
    
    void parseCurrentWeatherData(WiFiClient &json);  
    void parse5DayForecast(WiFiClient &json);
    void parseAirPollution(WiFiClient &json);
    int getDailyNr(int time);
};