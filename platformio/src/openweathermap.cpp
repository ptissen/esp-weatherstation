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

#include "openweathermap.h"

#include "config/secrets.h"
#include "config/config.h"
#include "logging.h"
#include "helper_conversions.h"
#include "helper_icons.h"
#include "helper.h"
#include "globalvar.h"

void OpenWeatherMap::update()
{
    m_isDataValid = false;
    m_isError = false;

    logI.println("\n------------ OWM -------------");

    logD.println("-- Current Weather");
    
    fetchWeatherData(WEATHER_DATA_TYPE::Current);
    if (m_isError)
        return;

    logD.println("-- Forecast Weather");
    fetchWeatherData(WEATHER_DATA_TYPE::Forecast);
    if (m_isError)
        return;

    logD.println("-- AirQuality");
    fetchWeatherData(WEATHER_DATA_TYPE::AirQuality);
    if (m_isError)
        return;

    logD.println("-- Convert Forecast to Daily");
    convert5DayToDaily();
    if (m_isError)
        return;

    m_isDataValid = true;
}

void OpenWeatherMap::fetchWeatherData(const WEATHER_DATA_TYPE dataType)
{
    logD.println("  Free memory: " + String(esp_get_free_heap_size()) + " bytes");

    const int MESSAGE_MAX_LENGTH = 20000;

    char url[150];
    switch (dataType)
    {
    case WEATHER_DATA_TYPE::Current:
        strncpy(url, OWM_WEATHER, sizeof(url));
        break;
    case WEATHER_DATA_TYPE::Forecast:
        strncpy(url, OWM_FORECAST, sizeof(url));
        break;
    case WEATHER_DATA_TYPE::AirQuality:
        strncpy(url, OWM_AIR_POLLUTION, sizeof(url));
        break;
    default:
        logW.println("  Invalid weather data type");
        m_isError = true;
        return;
    }
    logD.println("  URL: " + String(url));

    for (int i = 1; i <= OWM_ATTEMPS; ++i)
    {
        HTTPClient http;
        http.begin(m_client, OWM_ENDPOINT, OWM_HTTP_PORT, url);
        http.addHeader("Content-Type", "application/json");
        int responseCode = http.GET();
        if (responseCode == HTTP_CODE_OK)
        {
            if (http.getSize() > 0 && http.getSize() < MESSAGE_MAX_LENGTH)
            {
                switch (dataType)
                {
                case WEATHER_DATA_TYPE::Current:
                    try{
                        parseCurrentWeatherData(http.getStream());
                    }
                    catch (const std::exception &e) {
                            m_isError = true;
                            logW.print("Exception caught while parsing JSON data: ");
                            logW.println(e.what());
                    }
                    return;
                case WEATHER_DATA_TYPE::Forecast:
                    try{
                        parse5DayForecast(http.getStream());
                    }
                    catch (const std::exception &e) {
                            m_isError = true;
                            logW.print("Exception caught while parsing JSON data: ");
                            logW.println(e.what());
                    }
                    return;
                case WEATHER_DATA_TYPE::AirQuality:
                    try{
                        parseAirPollution(http.getStream());
                    }
                    catch (const std::exception &e) {
                            m_isError = true;
                            logW.print("Exception caught while parsing JSON data: ");
                            logW.println(e.what());
                    }
                    return;
                default:
                    logW.println("  Invalid weather data type");
                    m_isError = true;
                    http.end();
                    return;
                }
            }
            else
            {
                logW.println("  Response Content Length : " + String(http.getSize()));
                m_isError = true;
                http.end();
                return;
            }
        }
        else if (i == OWM_ATTEMPS)
        {
            logW.println("  Response Code : " + String(responseCode));
            m_isError = true;
            http.end();
            return;
        }
        http.end();

        delay(1000);
    }
}

int OpenWeatherMap::getDailyNr(int time)
{
    for (int i = 0; i < 6; i++)
    {
        if (TIME_isSameDay((time_t) time, (time_t) m_daily.day[i].dt))
        {
            return i;
        }
    }

    return -1;
}

void OpenWeatherMap::convert5DayToDaily()
{
    // Find min datetime
    int mindt = m_5df.list[0].dt;
    for (int i = 1; i < 40; i++)
    {
        mindt = min(mindt, m_5df.list[i].dt);
    }

    logD.println("  Min datetime    : " + String(mindt));

    // Set default data
    for (int i = 0; i < 6; i++)
    {
        m_daily.day[i].dt = mindt + i *(24 * 60 * 60);
        m_daily.day[i].temp_max = INT_MIN;
        m_daily.day[i].temp_min = INT_MAX;
        m_daily.day[i].rain = 0;
        m_daily.day[i].id = -1;
        m_daily.day[i].dataCount = 0;
    }

    for (int i = 0; i < 40; i++)
    {
        int j = getDailyNr(m_5df.list[i].dt);
        if (j < 0 || j >= 6)
            continue;
        
        //logD.println("  Mapping data: " + String(i) + " to day: " + String(j));

        m_daily.day[j].temp_min = min((int)roundf(m_5df.list[i].main.temp_min), m_daily.day[j].temp_min);
        m_daily.day[j].temp_max = max((int)roundf(m_5df.list[i].main.temp_max), m_daily.day[j].temp_max);
        m_daily.day[j].rain = max((int)roundf(m_5df.list[i].rain.h3), m_daily.day[j].rain);
        std::vector<int> vec;
        vec.push_back(m_5df.list[i].weather.id);
        vec.push_back(m_daily.day[j].id);
        m_daily.day[j].id = CONVERT_WEATHER_multipleConditionsToOne(vec);
        m_daily.day[j].dataCount++;
    }
}

void OpenWeatherMap::parseCurrentWeatherData(WiFiClient &json)
{
    DynamicJsonDocument m_doc(30*1024);
    logD.println("  Free memory: " + String(esp_get_free_heap_size()) + " bytes");
    logD.println("  Parse Current Weather data");

    DeserializationError error;
    try
    {
        DynamicJsonDocument filter(1024);
        filter["weather"][0]["id"] = true;
        filter["weather"][0]["icon"] = true;
        filter["main"]["temp"] = true;
        filter["main"]["feels_like"] = true;
        filter["main"]["temp_min"] = true;
        filter["main"]["temp_max"] = true;
        filter["main"]["pressure"] = true;
        filter["main"]["humidity"] = true;
        filter["wind"]["speed"] = true;
        filter["wind"]["deg"] = true;
        filter["rain"]["1h"] = true;
        filter["sys"]["sunrise"] = true;
        filter["sys"]["sunset"] = true;

        m_doc.clear();
        error = deserializeJson(m_doc, json,DeserializationOption::Filter(filter));
    }
    catch (const std::exception &e)
    {
        m_isError = true;
        logW.print("Exception caught while parsing JSON data: ");
        logW.println(e.what());
        return;
    }

    if (error)
    {
        logD.print("Fehler beim Parsen der JSON-Daten: ");
        logD.println(error.c_str());
        m_isError = true;
        return;
    }

    JsonObject weather = m_doc["weather"][0];
    m_cwd.weather.id = weather["id"];
    strncpy(m_cwd.weather.icon, weather["icon"], sizeof(m_cwd.weather.icon));

    JsonObject main = m_doc["main"];
    m_cwd.main.temp = main["temp"];
    m_cwd.main.feels_like = main["feels_like"];
    m_cwd.main.temp_min = main["temp_min"];
    m_cwd.main.temp_max = main["temp_max"];
    m_cwd.main.pressure = main["pressure"];
    m_cwd.main.humidity = main["humidity"];

    JsonObject wind = m_doc["wind"];
    m_cwd.wind.speed = wind["speed"];
    m_cwd.wind.deg = wind["deg"];

    JsonObject rain = m_doc["rain"];
    m_cwd.rain.h1 = rain["1h"];

    JsonObject sys = m_doc["sys"];
    m_cwd.sys.sunrise = sys["sunrise"];
    m_cwd.sys.sunset = sys["sunset"];

    m_doc.clear();
}

void OpenWeatherMap::parse5DayForecast(WiFiClient &json)
{
    DynamicJsonDocument m_doc(30*1024);
    logD.println("  Free memory: " + String(esp_get_free_heap_size()) + " bytes");
    logD.println("  Parse 5 Day Forecast");

    DeserializationError error;
    try
    {
        m_doc.clear();
        error = deserializeJson(m_doc, json);
    }
    catch (const std::exception &e)
    {
        m_isError = true;
        logW.print("Exception caught while parsing JSON data: ");
        logW.println(e.what());
        return;
    }

    if (error)
    {
        logD.print("Fehler beim Parsen der JSON-Daten: ");
        logD.println(error.c_str());
        m_isError = true;
        return;
    }

    JsonArray list = m_doc["list"];
    int index = 0;
    for (JsonObject item : list)
    {
        m_5df.list[index].dt = item["dt"];

        JsonObject main = item["main"];
        m_5df.list[index].main.temp = main["temp"];
        m_5df.list[index].main.feels_like = main["feels_like"];
        m_5df.list[index].main.temp_min = main["temp_min"];
        m_5df.list[index].main.temp_max = main["temp_max"];

        JsonObject weather = item["weather"][0];
        m_5df.list[index].weather.id = weather["id"];
        strncpy(m_5df.list[index].weather.icon, weather["icon"], sizeof(m_5df.list[index].weather.icon));

        JsonObject wind = item["wind"];
        m_5df.list[index].wind.speed = wind["speed"];
        m_5df.list[index].wind.deg = wind["deg"];
        m_5df.list[index].wind.gust = wind["gust"];
        m_5df.list[index].pop = item["pop"];

        JsonObject rain = item["rain"];
        m_5df.list[index].rain.h3 = rain["3h"];

        index++;
    }
    m_doc.clear();
}

void OpenWeatherMap::parseAirPollution(WiFiClient &json)
{
    DynamicJsonDocument m_doc(30*1024);
    logD.println("  Parse Air Pollution");

    DeserializationError error;
    try
    {
        DynamicJsonDocument filter(512);
        filter["list"][0]["dt"] = true;
        filter["list"][0]["main"]["aqi"] = true;
        m_doc.clear();
        error = deserializeJson(m_doc, json, DeserializationOption::Filter(filter));
    }
    catch (const std::exception &e)
    {
        m_isError = true;
        logW.print("Exception caught while parsing JSON data: ");
        logW.println(e.what());
        return;
    }

    if (error)
    {
        logW.print("Error parsing JSON data: ");
        logW.println(error.c_str());
        m_isError = true;
        return;
    }

    if (!m_doc.containsKey("list") || !m_doc["list"].is<JsonArray>())
    {
        logW.println("Error: 'list' key not found or not an array");
        m_isError = true;
        return;
    }

    if (!m_doc.containsKey("list") || !m_doc["list"].is<JsonArray>())
    {
        logW.println("Error: 'list' key not found or not an array");
        m_isError = true;
        return;
    }
    JsonArray list = m_doc["list"];
    for (int i = 0; i < list.size(); i++)
    {
        JsonObject item = list[i];
        if (!item.containsKey("dt") || !item["dt"].is<unsigned long>())
        {
            logW.println("Error: 'dt' key not found or not an unsigned long");
            m_isError = true;
            continue;
        }

        if (!item.containsKey("main") || !item["main"].is<JsonObject>())
        {
            logW.println("Error: 'ain' key not found or not an object");
            m_isError = true;
            continue;
        }

        m_ap.list[i].dt = item["dt"];
        m_ap.list[i].main.aqi = item["main"]["aqi"];
    }
    m_doc.clear();
}
