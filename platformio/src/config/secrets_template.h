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

// TODO: Rename this file to "secrets.h" and replace the placeholder secrets.
#pragma once

// --------------------------------------------------------------------------
// --- WIFI --- 
#define SECRET_WIFI_SSID            "Your SSID"
#define SECRET_WIFI_PASSWORD        "Your Passwd"

// --------------------------------------------------------------------------
// --- OpenWeatherMap ---
#define SECRET_OWM_APPID            "Your AppID"

// --------------------------------------------------------------------------
// --- MQTT ---

#define MQTT_BROKER                 "homeassistant.local"
#define MQTT_USERNAME               "Your Username"
#define MQTT_PASSWORD               "Your Password"
#define MQTT_PORT                   1883

#define MQTT_TOP_PREFIX             "weather-station"
#define MQTT_TOP_STATUS             "weather-station/status"
#define MQTT_TOP_BATTERY            "weather-station/battery"
#define MQTT_TOP_LAST_UPDATE        "weather-station/lastupdate"