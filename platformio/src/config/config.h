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
#include "secrets.h"

// --------------------------------------------------------------------------
// --- Main Config ---
#define USE_MQTT                        true
#define USE_CAPTIVE_PORTAL              true

// --------------------------------------------------------------------------
// --- Logger ---
// Set Debug Level (Serial Logging decreases performance and battery lifetime)
#define LOG_ERROR                       true
#define LOG_WARNING                     true
#define LOG_INFO                        true
#define LOG_DEBUG                       true
#define LOG_SERIAL_BAUDRATE             115200

// --------------------------------------------------------------------------
// --- Battery ---
#define BATTERY_PIN_ADC                 35
#define PREFS_WAS_BATTERY_LOW           "b1"
#define BATTERY_READ_COUNT              10
#define BATTERY_VOLTAGE_LOW             3.0
#define BATTERY_VMIN                    3.4
#define BATTERY_VMAX                    4.2

// --------------------------------------------------------------------------
// --- E-Paper ---
#define PIN_EPD_BUSY                    13
#define PIN_EPD_CS                       5
#define PIN_EPD_RST                     21
#define PIN_EPD_DC                      22
#define PIN_EPD_SCK                     18
#define PIN_EPD_MISO                    19
#define PIN_EPD_MOSI                    23

#define DISP_WIDTH                      800
#define DISP_HEIGHT                     480

// --------------------------------------------------------------------------
// --- Time ---
#define TIME_MAX_TRY                    5
#define TIME_NTP_SERVER1                "pool.ntp.org"
#define TIME_NTP_SERVER2                "time.nist.gov"
#define TIME_DAYLIGHTOFFSET             3600
#define TIME_GMT_OFFSET_SEC             3600

// --------------------------------------------------------------------------
// --- WiFi ---
#define WIFI_TIMEOUT_MILLIS             10000

// --------------------------------------------------------------------------
// --- OpenWeatherMap ---
#define  OWM_PREFIX              "https://api.openweathermap.org/data/2.5/"
#define  OWM_ENDPOINT            "api.openweathermap.org"
const uint16_t OWM_HTTP_PORT    = 80;
#define  OWM_PREF_WEATHER        "weather?"
#define  OWM_PREF_FORECAST       "forecast?"
#define  OWM_PREF_AIR_POLLUTION  "air_pollution?"

#define  OWM_CITY_STRING         "Aachen"
#define  OWM_LOC_ID              "3247449"
#define  OWM_LOC_LON             "6.083862"
#define  OWM_LOC_LAT             "50.776351"
#define  OWM_UNITS               "metric"
#define  OWM_LANG                "de"

#define  OWM_paramUnit           "units="  OWM_UNITS
#define  OWM_paramLang           "lang="   OWM_LANG
#define  OWM_paramAppID          "appid="  SECRET_OWM_APPID
#define  OWM_paramId             "id="     OWM_LOC_ID
#define  OWM_paramLat            "lat="    OWM_LOC_LAT
#define  OWM_paramLong           "lon="    OWM_LOC_LON

#define  OWM_POSTFIX             OWM_paramLat "&"  OWM_paramLong  "&" OWM_paramUnit  "&" OWM_paramLang "&" OWM_paramAppID

extern const char* OWM_WEATHER;
extern const char* OWM_FORECAST;
extern const char* OWM_AIR_POLLUTION;

const int OWM_AIR_POLLUTION_LISTCOUNT   = 1;
const int OWM_ATTEMPS                   = 3;

// --------------------------------------------------------------------------
// --- DeepSleep ---

const int DEEPSLEPP_START_H         = 23;
const int DEEPSLEPP_END_H           = 06;
const int SLEEP_NORM_MIN            = 10;
const int SLEEP_VLOW_MINUTES        = ((60 * 12));

// --------------------------------------------------------------------------
// --- Formating ---
#define FORMAT_TIME                     "%H:%M"
#define FORMAT_HOUR                     "%H"
#define FORMAT_DATE                     "%x"         
#define FORMAT_DATE_TIME                "%x %H:%M"

// --------------------------------------------------------------------------
// --- MQTT ---
#define MQTT_MAX_TRY                    5
#define MQTT_CLIENT_ID                  "WeatherStation-ESP32-EPD"
