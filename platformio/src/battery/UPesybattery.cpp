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

#include "UPesyBattery.h"

#include "config/config.h"
#include "config/secrets.h"
#include "logging.h"

void UPesyBattery::ini(void){
    pinMode(UPesyBattery_PIN_ADC, INPUT);
}

void UPesyBattery::update(void){
    logI.println("\n------------ UPesyBattery ------------");

    // Average the UPesyBattery voltage over multiple analog values for bestter results
    long sum = 0;
    for (int i = 0; i < UPesyBattery_READ_COUNT; i++)
    {
        sum += analogRead(UPesyBattery_PIN_ADC);
        delayMicroseconds(10);
    }

    // Calculate AnalogValue
    m_voltage = sum / (float) UPesyBattery_READ_COUNT;

    // Calculate the voltage
    m_voltage = 1.435 * (m_voltage / 4095.0) * 3.3;
    logD.println(" Voltage      : " + String(m_voltage));

    // Calculate the percentage
    m_percent = (int)round(((m_voltage - UPesyBattery_VMIN) / (UPesyBattery_VMAX - UPesyBattery_VMIN)) * 100);
    m_percent = max(0, min(100, m_percent));
    m_isUPesyBatteryLow = m_voltage <= UPesyBattery_VOLTAGE_LOW;

    logD.println(" Percentage   : " + String(m_percent));
    logD.println(" isLow ?      : " + String(m_isUPesyBatteryLow));

    // Check Memory for last state of UPesyBattery
    myPrefs.begin(PREFS_WAS_UPesyBattery_LOW, false);
    m_wasUPesyBatteryLow = myPrefs.getBool(PREFS_WAS_UPesyBattery_LOW, false);
    logD.println(" wasLow       : " + String(m_wasUPesyBatteryLow));
    if (m_isUPesyBatteryLow && !m_wasUPesyBatteryLow) {
        myPrefs.putBool(PREFS_WAS_UPesyBattery_LOW, true);
    }
    if (!m_isUPesyBatteryLow && m_wasUPesyBatteryLow) {
        myPrefs.putBool(PREFS_WAS_UPesyBattery_LOW, false);
    }
    myPrefs.end();
}