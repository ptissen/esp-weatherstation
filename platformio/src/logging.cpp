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

#include "logging.h"

#include "config/config.h"
#include "version/version.h"

void logInit() {
    #if LOG_ISACTIVATED
        Serial.begin(LOG_SERIAL_BAUDRATE);
    #endif

    // Uncomment to wait for command (easy way to catch all logs)
    //while (!logSerial.available()){}
    logI.println("\n");
    logI.println("-----------------------------------");
    logI.println("------------ WeatherStation -------");    
    logI.println("-----------------------------------");
    logI.println("\n------------ Logging --------------");
    logD.println("  Baudrate    : " + String(LOG_SERIAL_BAUDRATE));
    logD.println("  Free memory: " + String(esp_get_free_heap_size()) + " bytes");

    char cmd[50];
    if(Serial.available()){
        size_t len = Serial.readBytesUntil('\n', cmd, sizeof(cmd) - 1);
        cmd[len] = '\0';
        logI.println("Your command: " + String(cmd));
    }
    logI.println("\n------------ Version ------------");
    logI.println("  Version     : " + String(VERSION_INFO));
    logI.println("  Author      : " + String(VERSION_AUTHOR));
    logI.println("  Date        : " + String(__DATE__) + " " + String(__TIME__));
}