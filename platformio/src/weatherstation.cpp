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

#include "weatherstation.h"

#include "logging.h"
#include "globalvar.h"
#include "config/config.h"
#include "config/secrets.h"

void WeatherStation::ini(){
    logInit();

    // Check System Status
    if(!isBootReasonOk()){
        activateDeepSleep(true,m_timeHandler);
        return;
    }
   
    // Battery
    m_battery.init();
    m_battery.update();
    if(m_battery.isBatteryLow() == true) {
        if(m_battery.wasBatteryLow() == false){
            m_displayHandler.drawError(DisplayHandler::ERR_BATTERY);
        }
        activateDeepSleep(true,m_timeHandler);
        return;
    }

    // WIFI
    m_wifiHandler.ini();
    m_wifiHandler.update();
    if(!m_wifiHandler.isConnected()){
        m_wifiHandler.kill();
        m_displayHandler.drawError(DisplayHandler::ERR_WIFI);
        activateDeepSleep(false,m_timeHandler);
        return;
    }

    // Time
    m_timeHandler.ini();
    m_timeHandler.update();
    if(!m_timeHandler.isValid()){
        m_wifiHandler.kill();
        m_displayHandler.drawError(DisplayHandler::ERR_TIME);
        activateDeepSleep(false,m_timeHandler);
        return;
    }

    // OWM
    m_owm.update();
    if(m_owm.isError()){
        m_wifiHandler.kill();
        m_displayHandler.drawError(DisplayHandler::ERR_API);
        activateDeepSleep(false,m_timeHandler);
        return;
    }

    #if (USE_MQTT == true)
        MQTTHandler m_mqtt(m_client);
        m_mqtt.setup();
        m_mqtt.publish(MQTT_TOP_BATTERY,String(m_battery.percent()).c_str());
        m_wifiHandler.kill();
    #endif

    GL_BAT_PERCENTAGE = m_battery.percent();
    GL_BAT_VOLTAGE = m_battery.voltage();
    GL_WIFI_DBM = m_wifiHandler.rssi();
    GL_TIME_LASTUPDATE = m_timeHandler.lastUpdate();

    m_displayHandler.update(m_owm);
    activateDeepSleep(false,m_timeHandler);
}

void WeatherStation::testDisplay(){
    const int TEST_DELAY = 80000; // 10s

    delay(TEST_DELAY);
    m_displayHandler.drawError(DisplayHandler::ERR_API);
    delay(TEST_DELAY);
    m_displayHandler.drawError(DisplayHandler::ERR_BATTERY);
    delay(TEST_DELAY);
    m_displayHandler.drawError(DisplayHandler::ERR_SYSTEM);
    delay(TEST_DELAY);
    m_displayHandler.drawError(DisplayHandler::ERR_TIME);
    delay(TEST_DELAY);  
    m_displayHandler.drawError(DisplayHandler::ERR_WIFI);
    delay(TEST_DELAY);
}

 void WeatherStation::activateDeepSleep(bool forever, TimeHandler &t) {
    logD.println("\n------------ DeepSleep ----------");
    delay(1);

    if (forever) {
        // Sleep forever
        logI.print("  Activate Deepsleep: forever");
        esp_sleep_enable_timer_wakeup(0);
        esp_deep_sleep_start();
        return;
    }

    uint64_t sleepTime = 0;

    if(t.isValid()){
        tm * ts= t.lastUpdate();
    
        if(ts->tm_hour >= DEEPSLEPP_START_H || ts->tm_hour < DEEPSLEPP_END_H){
            tm zielZeit = *ts;  
            zielZeit.tm_hour = DEEPSLEPP_END_H;
            zielZeit.tm_min = 0;      
            zielZeit.tm_sec = 0;     

            time_t wakeTime = mktime(&zielZeit); 

            if(ts->tm_hour >= DEEPSLEPP_START_H){
                wakeTime += (24*60*60);
            }

            time_t currTime = mktime(ts);
            logD.println("  Wake up time    : " + String(wakeTime));
            logD.println("  Curr Time       : " + String(currTime));
            
            sleepTime = (uint64_t) difftime(wakeTime, currTime);
        }else{
            // Default Sleep Time
            sleepTime = 10 * 60;
        }
    }
    else{
        // No Valid  Time given
        sleepTime = 10 * 60;
    }

    logI.print("  Activate Deepsleep (s): " + String(sleepTime) + "\n");

    esp_sleep_enable_timer_wakeup(sleepTime * 1000000);
    esp_deep_sleep_start();
}


bool WeatherStation::isBootReasonOk(){
     // Lese den Grund für den letzten Neustart aus
    logD.println("\n------------ System ----------");
    ++SYS_BOOT_COUNT;
    logD.println("  Boot number: " + String(SYS_BOOT_COUNT));

    esp_reset_reason_t reason = esp_reset_reason();
    switch (reason) {
    case ESP_RST_PANIC:
        logW.println("  Software-Reset due to Exception/Panic");
        return false;
    case ESP_RST_INT_WDT:
        logW.println("  Reset due to Interrupt Watchdog");
        return false;
    case ESP_RST_TASK_WDT:
        logW.println("  Reset due to Task Watchdog");
        return false;
    case ESP_RST_WDT:
        logW.println("  Reset due to other Watchdogs");
        return false;

    case ESP_RST_POWERON:
        logD.println("  PowerOn-Reset");
        break;
    case ESP_RST_SW:
        logD.println("  Software Reset");
        break;
    case ESP_RST_DEEPSLEEP:
        logD.println("  Reset after exiting Deep Sleep mode");
        break;
    case ESP_RST_BROWNOUT:
        logD.println("  Brownout Reset");
        break;
    case ESP_RST_SDIO:
        logD.println("  Reset due to SDIO");
        break;
    case ESP_RST_UNKNOWN:
    default:
        logW.println("  Unknown Reset Reason");
        break;
    }

    return true;
}