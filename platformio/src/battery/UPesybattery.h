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
#include <Preferences.h>

// --------------------------------------------------------------------------
// --- Battery ---
#define BATTERY_PIN_ADC                 35
#define PREFS_WAS_BATTERY_LOW           "b1"
#define BATTERY_READ_COUNT              10
#define BATTERY_VOLTAGE_LOW             3.0
#define BATTERY_VMIN                    3.4
#define BATTERY_VMAX                    4.2
// --------------------------------------------------------------------------

class UPesyBattery : public Battery {
public:
    UPesyBattery() = default;

    void init() override;
    void update() override;

    int percent() const override { return m_percent; }
    float voltage() const override { return m_voltage; }
    bool isBatteryLow() const override { return m_isBatteryLow; }
    bool wasBatteryLow() const override { return m_wasBatteryLow; }

private:
    float m_voltage = 0.0;
    int m_percent = 0; 
    bool m_isBatteryLow = false;
    bool m_wasBatteryLow = false;
    Preferences myPrefs;
};